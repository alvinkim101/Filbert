#include "Window.h"
#include "Platform/OpenGL/OpenGLWindow.h"
#include "Filbert/Renderer/Renderer.h"

namespace Filbert
{
	Window* Window::Create(const WindowProps& props)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLWindow(props);

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}
}
