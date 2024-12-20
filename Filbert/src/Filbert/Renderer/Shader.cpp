#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Filbert
{
	Shader* Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(name, vertexSource, fragmentSource);

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}

	Shader* Shader::Create(const std::string& name, const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(name, filePath);

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name) const
	{
		try
		{
			return m_shaders.at(name);
		}
		catch (const std::out_of_range& e)
		{
			FB_CORE_ASSERT(false, "Shader with specified name does not exist");
			return nullptr;
		}
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		FB_CORE_ASSERT(!m_shaders.count(shader->GetName()), "Shader with specified name already exists");
		m_shaders[shader->GetName()] = shader;
	}

	void ShaderLibrary::Remove(const std::shared_ptr<Shader>& shader)
	{
		FB_CORE_ASSERT(m_shaders.count(shader->GetName()), "Shader with specified name does not exist");
		m_shaders.erase(shader->GetName());
	}

	void ShaderLibrary::Clear()
	{
		m_shaders.clear();
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		FB_CORE_ASSERT(!m_shaders.count(name), "Shader with specified name already exists");
		std::shared_ptr<Shader> shader(Shader::Create(name, filePath));
		m_shaders[name] = shader;

		return shader;
	}
}
