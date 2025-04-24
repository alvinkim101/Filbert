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
		Framebuffer(const FramebufferSpec& spec) : m_framebufferSpec(spec) {}
		virtual ~Framebuffer() = default;

		virtual void Recreate(const FramebufferSpec& spec) = 0;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual unsigned int GetColorAttachment() = 0;
		virtual unsigned int GetDepthStencilAttachment() = 0;

		const FramebufferSpec& GetSpecification() const { return m_framebufferSpec; }

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpec& spec);

	protected:
		FramebufferSpec m_framebufferSpec;
	};
}
