#include "OpenGLRendererAPI.h"

#include <glad/gl.h>

namespace Filbert
{
	void OpenGLRendererAPI::Initialize()
	{
		glEnable(GL_DEPTH_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void OpenGLRendererAPI::SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count)
	{
		if (count == 0)
		{
			count = vertexArray->GetElementBuffer()->GetCount();
		}

		// TODO: Remove hardcoded mode and type
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}
