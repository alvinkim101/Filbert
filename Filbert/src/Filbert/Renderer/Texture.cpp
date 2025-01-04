#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Filbert
{
	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& fileName)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(fileName);

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}

	std::shared_ptr<Texture2D> Texture2D::Create(int width, int height)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(width, height);

		default:
			FB_CORE_ASSERT(false, "Current renderer API not supported");
			return nullptr;
		}
	}
}
