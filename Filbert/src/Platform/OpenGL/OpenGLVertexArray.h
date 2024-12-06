#pragma once

#include "Filbert/Renderer/VertexArray.h"

namespace Filbert
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) override;

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_vertexBuffers; }
		const std::shared_ptr<ElementBuffer>& GetElementBuffer() const override { return m_elementBuffer; }

	private:
		unsigned int m_vao = 0;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		std::shared_ptr<ElementBuffer> m_elementBuffer;
		unsigned int m_attributeIndex = 0;
	};
}
