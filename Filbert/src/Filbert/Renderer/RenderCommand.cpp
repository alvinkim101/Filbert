#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Filbert
{
	std::unique_ptr<RendererAPI> RenderCommand::s_rendererAPI = RendererAPI::Create();
}
