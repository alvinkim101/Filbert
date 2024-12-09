#pragma once

#include "Filbert/Renderer/RendererAPI.h"

namespace Filbert
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawElements(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
