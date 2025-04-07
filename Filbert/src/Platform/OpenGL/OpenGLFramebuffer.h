#pragma once

#include <Filbert/Renderer/Framebuffer.h>

namespace Filbert
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpec& spec);
		~OpenGLFramebuffer();

		void Bind() override;
		void Unbind() override;

		unsigned int GetColorAttachment() override { return m_colorAttachment; }
		unsigned int GetDepthStencilAttachment() override { return m_depthStencilAttachment; }

	private:
		unsigned int m_frameBuffer{};
		unsigned int m_colorAttachment{};
		unsigned int m_depthStencilAttachment{};
	};
}
