#pragma once

#include "Filbert/Renderer/Buffer.h"

namespace Filbert
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(void* data, unsigned int size);
		~OpenGLVertexBuffer() override;

		unsigned int GetID() const override { return m_vbo; }
		void SetLayout(const BufferLayout& layout) override;
		const BufferLayout& GetLayout() const override;

	private:
		unsigned int m_vbo = 0;
		BufferLayout m_layout;
	};

	class OpenGLElementBuffer : public ElementBuffer
	{
	public:
		OpenGLElementBuffer(unsigned int vertices[], unsigned int size);
		~OpenGLElementBuffer() override;

		unsigned int GetID() const override { return m_ebo; }
		unsigned int GetCount() const override { return m_count; }

	private:
		unsigned int m_ebo = 0;
		unsigned int m_count = 0;
	};
}
