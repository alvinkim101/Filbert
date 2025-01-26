#include "OpenGLBuffer.h"

#include <glad/gl.h>

namespace Filbert
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size)
	{
		glCreateBuffers(1, &m_vbo);
		glNamedBufferStorage(m_vbo, size, nullptr, GL_DYNAMIC_STORAGE_BIT);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(void* data, unsigned int size)
	{
		glCreateBuffers(1, &m_vbo);
		glNamedBufferStorage(m_vbo, size, data, GL_DYNAMIC_STORAGE_BIT);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_vbo);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_layout = layout;
	}

	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		return m_layout;
	}

	void OpenGLVertexBuffer::SetData(void* data, unsigned int size)
	{
		glNamedBufferSubData(m_vbo, 0, size, data);
	}

	OpenGLElementBuffer::OpenGLElementBuffer(unsigned int indices[], unsigned int size)
	{
		glCreateBuffers(1, &m_ebo);
		glNamedBufferStorage(m_ebo, size, indices, GL_DYNAMIC_STORAGE_BIT);

		m_count = size / sizeof(unsigned int);
	}

	OpenGLElementBuffer::~OpenGLElementBuffer()
	{
		glDeleteBuffers(1, &m_ebo);
	}
}
