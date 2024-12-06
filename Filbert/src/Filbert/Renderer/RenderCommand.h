#pragma once

#include "RendererAPI.h"

namespace Filbert
{
	class RenderCommand
	{
	public:
		static void SetClearColor(const glm::vec4& color) { s_rendererAPI->SetClearColor(color); }
		static void Clear() { s_rendererAPI->Clear(); }

		static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray) { s_rendererAPI->DrawElements(vertexArray); }

	private:
		static RendererAPI* s_rendererAPI;
	};
}
