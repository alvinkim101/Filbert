#pragma once

#include <glm/mat4x4.hpp>

namespace Filbert
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual unsigned int GetID() const = 0;
		virtual const std::string& GetName() const = 0;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& vector) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& vector) = 0;
		virtual void SetInt(const std::string& name, int integer) = 0;

		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& filePath);
	};

	class ShaderLibrary
	{
	public:
		std::shared_ptr<Shader> Get(const std::string& name) const;

		void Add(const std::shared_ptr<Shader>& shader);
		void Remove(const std::shared_ptr<Shader>& shader);
		void Clear();

		std::shared_ptr<Shader> Load(const std::string& name, const std::string& filePath);

	private:
		std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
	};
}
