#pragma once

namespace Filbert
{
	enum class RendererAPI
	{
		None,
		OpenGL
	};

	class Renderer
	{
	public:
		static RendererAPI GetAPI() { return s_api; }

	private:
		static RendererAPI s_api;
	};
}
