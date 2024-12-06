#include "Context.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Filbert
{
	Context* Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return new OpenGLContext(static_cast<GLFWwindow*>(window));

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}
}
