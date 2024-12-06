#include "OpenGLVertexArray.h"

#include <glad/gl.h>

namespace Filbert
{
	namespace
	{
		GLenum ShaderDataTypeToGLenum(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::Float:
			case ShaderDataType::Float2:
			case ShaderDataType::Float3:
			case ShaderDataType::Float4:
				return GL_FLOAT;

			default:
				FB_CORE_ASSERT(false, "No valid conversion to GLenum");
				return 0;
			}
		}
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_vao);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_vao);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_vao);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		unsigned int bindingIndex = static_cast<unsigned int>(m_vertexBuffers.size());
		auto layout = vertexBuffer->GetLayout();

		glVertexArrayVertexBuffer(m_vao, bindingIndex, vertexBuffer->GetID(), 0, layout.GetStride());

		// Attribute index ordered by insertion
		for (const auto& element : layout.GetElements())
		{
			glVertexArrayAttribBinding(m_vao, m_attributeIndex, bindingIndex);
			glVertexArrayAttribFormat(m_vao, m_attributeIndex, ShaderDataTypeCount(element.type), ShaderDataTypeToGLenum(element.type), element.normalized, element.offset);
			glEnableVertexArrayAttrib(m_vao, m_attributeIndex);

			m_attributeIndex++;
		}

		m_vertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer)
	{
		glVertexArrayElementBuffer(m_vao, elementBuffer->GetID());

		m_elementBuffer = elementBuffer;
	}
}
