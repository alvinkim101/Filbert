#pragma once

namespace Filbert
{
	struct FramebufferSpec
	{
		unsigned int width;
		unsigned int height;
	};

	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpec& spec) : m_frameBufferSpec(spec) {}
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetColorAttachment() = 0;
		virtual unsigned int GetDepthStencilAttachment() = 0;

		const FramebufferSpec& GetSpecification() const { return m_frameBufferSpec; }

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpec& spec);

	protected:
		FramebufferSpec m_frameBufferSpec;
	};
}
