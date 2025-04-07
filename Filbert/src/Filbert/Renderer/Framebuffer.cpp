#include "Framebuffer.h"

#include <Filbert/Renderer/Renderer.h>
#include <Platform/OpenGL/OpenGLFramebuffer.h>

namespace Filbert
{
	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpec& spec)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLFramebuffer>(spec);

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}
}
