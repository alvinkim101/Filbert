#pragma once

#include "VertexArray.h"

#include <glm/vec4.hpp>

namespace Filbert
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None,
			OpenGL
		};

		virtual void Initialize() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawElements(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return s_api; }
		static RendererAPI* Create();

	private:
		static API s_api;
	};
}
