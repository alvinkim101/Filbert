#pragma once

#include "Buffer.h"

namespace Filbert
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {};

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetElementBuffer(const std::shared_ptr<ElementBuffer>& elementBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<ElementBuffer>& GetElementBuffer() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};
}
