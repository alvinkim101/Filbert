#pragma once

#include "RendererAPI.h"

namespace Filbert
{
	class RenderCommand
	{
	public:
		static void Initialize() { s_rendererAPI->Initialize(); }

		static void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) { s_rendererAPI->SetViewport(x, y, width, height); }

		static void SetClearColor(const glm::vec4& color) { s_rendererAPI->SetClearColor(color); }
		static void Clear() { s_rendererAPI->Clear(); }

		static void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count = 0) { s_rendererAPI->DrawElements(vertexArray, count); }

	private:
		static std::unique_ptr<RendererAPI> s_rendererAPI;
	};
}
