#include "OpenGLShader.h"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace Filbert
{
	namespace
	{
		const std::unordered_map<std::string, GLenum> nameToEnum =
		{
			{ "vertex", GL_VERTEX_SHADER },
			{ "fragment", GL_FRAGMENT_SHADER }
		};
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		std::unordered_map<GLenum, std::string> shaderMap;
		shaderMap[GL_VERTEX_SHADER] = vertexSource;
		shaderMap[GL_FRAGMENT_SHADER] = fragmentSource;

		Compile(shaderMap);
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string source = ReadFile(filePath);
		std::unordered_map<GLenum, std::string> shaderMap = ParseSource(source);

		Compile(shaderMap);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_program); // Also detaches shaders
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath)
	{
		std::string source;
		std::ifstream ifs(filePath);
		std::stringstream ss;

		if (ifs)
		{
			ss << ifs.rdbuf();
			source = ss.str();
		}
		else
		{
			FB_CORE_WARN("Could not open file {}", filePath);
		}

		return source;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::ParseSource(const std::string& source)
	{
		constexpr std::string_view delimiter = "#type";
		constexpr std::string_view eol = "\r\n";

		std::unordered_map<GLenum, std::string> shaderMap;
		GLenum shaderType = 0;
		std::size_t delimiterPos = source.find(delimiter);
		FB_CORE_ASSERT(delimiterPos != std::string::npos, "Couldn't find delimiter");

		while (delimiterPos != std::string::npos)
		{
			// Parse shader type
			std::size_t start = delimiterPos + delimiter.size() + 1;
			std::size_t end = source.find_first_of(eol, start);
			std::string shaderTypeString = source.substr(start, end - start);

			// Convert shader type from string to GLenum
			try
			{
				shaderType = nameToEnum.at(shaderTypeString);
			}
			catch (const std::out_of_range& e)
			{
				FB_CORE_ASSERT(false, "Invalid shader type");
			}

			// Store shader source code found between after eol and next delimiter if it exists
			FB_CORE_ASSERT(!shaderMap.count(shaderType), "Duplicate shader type");
			start = source.find_first_not_of(eol, end);
			end = source.find(delimiter, start);
			shaderMap[shaderType] = source.substr(start, end - start);

			delimiterPos = end;
		}

		for (const auto& i : shaderMap)
		{
			FB_CORE_INFO("{}", i.second);
		}

		FB_CORE_ASSERT(shaderMap.size(), "Shader map is empty");
		return shaderMap;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderMap)
	{
		constexpr uint8_t maxShaders = 6;
		std::array<GLuint, maxShaders> shaders;
		uint8_t shaderIndex = 0;

		// https://en.cppreference.com/w/cpp/language/structured_binding
		for (const auto& [shaderType, shaderSource] : shaderMap)
		{
			// Create an empty shader handle
			GLuint shader = glCreateShader(shaderType);

			// Send the vertex shader source code to GL
			// Note that std::string's .c_str is NULL character terminated.
			const GLchar* source = (const GLchar*)shaderSource.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shaders anymore.
				for (int i = 0; i < shaderIndex; i++)
				{
					glDeleteShader(shaders[i]);
				}
				glDeleteShader(shader);

				// Use the infoLog as you see fit.
				FB_CORE_ASSERT(false, infoLog.data());
				return;
			}

			shaders[shaderIndex++] = shader;
		}

		// Shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		for (int i = 0; i < shaderIndex; i++)
		{
			glAttachShader(program, shaders[i]);
		}

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (int i = 0; i < shaderIndex; i++)
			{
				glDeleteShader(shaders[i]);
			}

			// Use the infoLog as you see fit.
			FB_CORE_ASSERT(false, infoLog.data());
			return;
		}

		// Assign after successful linkage
		m_program = program;

		// Always detach shaders after a successful link.
		// Shader deletion is deferred until detached from program
		for (int i = 0; i < shaderIndex; i++)
		{
			glDetachShader(program, shaders[i]);
			glDeleteShader(shaders[i]);
		}
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_program);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::mat4& matrix)
	{
		auto uniform = glGetUniformLocation(m_program, name.c_str());
		glProgramUniformMatrix4fv(m_program, uniform, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniform(const std::string& name, const glm::vec3& vector)
	{
		auto uniform = glGetUniformLocation(m_program, name.c_str());
		glProgramUniform3fv(m_program, uniform, 1, glm::value_ptr(vector));
	}

	void OpenGLShader::UploadUniform(const std::string& name, int integer)
	{
		auto uniform = glGetUniformLocation(m_program, name.c_str());
		glProgramUniform1i(m_program, uniform, integer);
	}
}
