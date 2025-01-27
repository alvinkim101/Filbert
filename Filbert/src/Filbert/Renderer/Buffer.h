#pragma once

namespace Filbert
{
	enum class ShaderDataType
	{
		None,
		Float, Float2, Float3, Float4,
		Int
	};

	namespace
	{
		constexpr unsigned int ShaderDataTypeSize(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::None:
				return 0;

			case ShaderDataType::Float:
				return 4;
			case ShaderDataType::Float2:
				return 8;
			case ShaderDataType::Float3:
				return 12;
			case ShaderDataType::Float4:
				return 16;
			case ShaderDataType::Int:
				return 4;

			default:
				FB_CORE_ASSERT(false, "Shader data type size unknown");
				return 0;
			}
		}

		constexpr unsigned int ShaderDataTypeCount(ShaderDataType type)
		{
			switch (type)
			{
			case ShaderDataType::None:
				return 0;

			case ShaderDataType::Float:
				return 1;
			case ShaderDataType::Float2:
				return 2;
			case ShaderDataType::Float3:
				return 3;
			case ShaderDataType::Float4:
				return 4;
			case ShaderDataType::Int:
				return 1;

			default:
				FB_CORE_ASSERT(false, "Shader data type size unknown");
				return 0;
			}
		}
	}

	struct BufferElement
	{
		BufferElement(const std::string& name, ShaderDataType type, bool normalized = false) : name(name), type(type), normalized(normalized), size(ShaderDataTypeSize(type)) {}

		std::string name;
		unsigned int size;
		ShaderDataType type;
		bool normalized;
		unsigned int offset;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements)
		{
			m_stride = 0;
			unsigned int offset = 0;

			for (auto& element : m_elements)
			{
				element.offset = offset;
				offset += element.size;

				m_stride += element.size;
			}
		}

		const std::vector<BufferElement>& GetElements() const { return m_elements; }
		const unsigned int GetStride() const { return m_stride; }

	private:
		std::vector<BufferElement> m_elements;
		unsigned int m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {};

		virtual unsigned int GetID() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		virtual void SetData(void* data, unsigned int size) = 0;

		static std::shared_ptr<VertexBuffer> Create(unsigned int size);
		static std::shared_ptr<VertexBuffer> Create(void* data, unsigned int size);
	};

	class ElementBuffer
	{
	public:
		virtual ~ElementBuffer() {};

		virtual unsigned int GetID() const = 0;
		virtual unsigned int GetCount() const = 0;

		static std::shared_ptr<ElementBuffer> Create(unsigned int indices[], unsigned int size);
	};
}
