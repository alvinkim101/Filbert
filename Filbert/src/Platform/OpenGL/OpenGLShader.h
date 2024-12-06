#pragma once

#include "Filbert/Renderer/Shader.h"

namespace Filbert
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource); // Not using std::string_view because C string is required
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

	private:
		unsigned int m_program = 0;
	};
}
