#pragma once

#include "Filbert/Renderer/Shader.h"

namespace Filbert
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource); // Not using std::string_view because C string is required
		~OpenGLShader() override;

		unsigned int GetID() const override { return m_program; }
		void Bind() const override;
		void Unbind() const override;

		void UploadUniform(const std::string& name, const glm::mat4& matrix) override;
		void UploadUniform(const std::string& name, const glm::vec3& vector) override;
		void UploadUniform(const std::string& name, int integer) override;

	private:
		unsigned int m_program = 0;
	};
}
