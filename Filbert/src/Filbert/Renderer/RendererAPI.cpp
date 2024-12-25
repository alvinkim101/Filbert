#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Filbert
{
	// TODO: Remove hardcoded renderer API
	RendererAPI::API RendererAPI::s_api = RendererAPI::API::OpenGL;

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (s_api)
		{
		case RendererAPI::API::OpenGL:
			return std::make_unique<OpenGLRendererAPI>();

		default:
			FB_CORE_ASSERT(false, "Invalid renderer API");
			return nullptr;
		}
	}
}
