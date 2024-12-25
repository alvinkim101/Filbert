#include "Input.h"
#include "Platform/OpenGL/OpenGLInput.h"
#include "Filbert/Renderer/Renderer.h"

namespace Filbert
{
	std::unique_ptr<Input> Input::s_input = Input::Create();

	std::unique_ptr<Input> Input::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLInput>();

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}
}
