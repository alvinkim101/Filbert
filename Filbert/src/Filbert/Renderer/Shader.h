#pragma once

#include <glm/mat4x4.hpp>

namespace Filbert
{
	class Shader
	{
	public:
		virtual ~Shader() {};

		virtual unsigned int GetID() const = 0;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniform(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniform(const std::string& name, const glm::vec3& vector) = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}
