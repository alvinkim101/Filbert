#pragma once

#include "Filbert/Renderer/Shader.h"

namespace Filbert
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource); // Not using std::string_view because C string is required
		OpenGLShader(const std::string& name, const std::string& filePath);

		~OpenGLShader() override;

		unsigned int GetID() const override { return m_program; }
		const std::string& GetName() const override { return m_name; }

		void Bind() const override;
		void Unbind() const override;

		void SetMat4(const std::string& name, const glm::mat4& matrix) override;
		void SetVec3(const std::string& name, const glm::vec3& vector) override;
		void SetInt(const std::string& name, int integer) override; // Used for textures

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<unsigned int, std::string> ParseSource(const std::string& source);
		void Compile(const std::unordered_map<unsigned int, std::string>& shaderMap);

		unsigned int m_program = 0;
		std::string m_name;
	};
}
