#include "OpenGLFramebuffer.h"

#include <glad/gl.h>

namespace Filbert
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec) : Framebuffer(spec)
	{
		// DSA https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions?tab=readme-ov-file#glframebuffer

		// Framebuffer
		glCreateFramebuffers(1, &m_frameBuffer);

		// Color attachment
		glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
		glTextureStorage2D(m_colorAttachment, 1, GL_RGBA8, m_frameBufferSpec.width, m_frameBufferSpec.height);
		glNamedFramebufferTexture(m_frameBuffer, GL_COLOR_ATTACHMENT0, m_colorAttachment, 0);

		// Depth + stencil attachment
		glCreateTextures(GL_TEXTURE_2D, 1, &m_depthStencilAttachment);
		glTextureStorage2D(m_depthStencilAttachment, 1, GL_DEPTH24_STENCIL8, m_frameBufferSpec.width, m_frameBufferSpec.height);
		glNamedFramebufferTexture(m_frameBuffer, GL_DEPTH_STENCIL_ATTACHMENT, m_depthStencilAttachment, 0);

		FB_CORE_ASSERT(glCheckNamedFramebufferStatus(m_frameBuffer, GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer not completed: {}", glCheckNamedFramebufferStatus(m_frameBuffer, GL_FRAMEBUFFER));
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_frameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}
