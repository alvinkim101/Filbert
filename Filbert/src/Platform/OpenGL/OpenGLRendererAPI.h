#pragma once

#include "Filbert/Renderer/RendererAPI.h"

namespace Filbert
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Initialize() override;

		void SetViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawElements(const std::shared_ptr<VertexArray>& vertexArray, unsigned int count = 0) override;
	};
}
