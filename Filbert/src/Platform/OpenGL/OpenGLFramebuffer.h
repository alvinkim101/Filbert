#pragma once

#include <Filbert/Renderer/Framebuffer.h>

namespace Filbert
{
	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpec& spec);
		~OpenGLFramebuffer();

		void Recreate(const FramebufferSpec& spec) override;

		void Bind() override;
		void Unbind() override;

		unsigned int GetColorAttachment() override { return m_colorAttachment; }
		unsigned int GetDepthStencilAttachment() override { return m_depthStencilAttachment; }

	private:
		void Create();
		void Destroy();

		unsigned int m_framebuffer{};
		unsigned int m_colorAttachment{};
		unsigned int m_depthStencilAttachment{};
	};
}
