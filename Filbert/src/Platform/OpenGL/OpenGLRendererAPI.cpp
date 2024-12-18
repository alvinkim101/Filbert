#include "OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace Filbert
{
	void OpenGLRendererAPI::Initialize()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
	{
		// TODO: Remove hardcoded mode and type
		glDrawElements(GL_TRIANGLES, vertexArray->GetElementBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}
