#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Filbert
{
	namespace
	{
		struct QuadVertex
		{
			glm::vec3 position;
			glm::vec4 color;
			glm::vec2 textureCoordinates;
		};

		struct Renderer2DData
		{
			// If exceed max, another draw call is needed
			// # of draw calls = (quads / maxQuads + 1) + 1
			static constexpr unsigned int maxQuads = 10000;
			static constexpr unsigned int maxVertices = maxQuads * 4;
			static constexpr unsigned int maxIndices = maxQuads * 6;

			std::shared_ptr<VertexArray> vertexArray;
			std::shared_ptr<VertexBuffer> vertexBuffer;
			std::shared_ptr<Shader> shader;

			unsigned int quadIndexCount = 0;
			QuadVertex* quadBufferBase = nullptr;
			QuadVertex* quadBufferOffset = nullptr;
		};

		Renderer2DData data;

		std::shared_ptr<Texture2D> whiteTexture;
		const glm::vec4 whiteColor = glm::vec4(1.0f);
	}

	void Renderer2D::Initialize()
	{
		whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));

		// Vertex buffer
		BufferLayout quadLayout =
		{
			{ "position", ShaderDataType::Float3 },
			{ "color", ShaderDataType::Float4 },
			{ "textureCoordinates", ShaderDataType::Float2 }
		};
		data.quadBufferBase = new QuadVertex[Renderer2DData::maxVertices];
		data.vertexBuffer = VertexBuffer::Create(Renderer2DData::maxVertices * sizeof(QuadVertex));
		data.vertexBuffer->SetLayout(quadLayout);

		// Element buffer
		unsigned int* quadIndices = new unsigned int[Renderer2DData::maxIndices];
		for (unsigned int i = 0, offset = 0; i < data.maxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		std::shared_ptr<ElementBuffer> elementBuffer;
		elementBuffer = ElementBuffer::Create(quadIndices, Renderer2DData::maxIndices * sizeof(unsigned int));
		delete[] quadIndices;

		// Vertex array
		data.vertexArray = VertexArray::Create();
		data.vertexArray->AddVertexBuffer(data.vertexBuffer);
		data.vertexArray->SetElementBuffer(elementBuffer);

		// Shader
		data.shader = Shader::Create("Color", "assets/shaders/Color.glsl");
	}

	void Renderer2D::Deinitialize()
	{
		delete[] data.quadBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		data.vertexArray->Bind();
		data.shader->Bind();
		data.shader->SetMat4("u_viewProjection", camera.GetViewProjection());

		data.quadIndexCount = 0;
		data.quadBufferOffset = data.quadBufferBase;
	}

	void Renderer2D::EndScene()
	{
		unsigned int size = (data.quadBufferOffset - data.quadBufferBase) * sizeof(QuadVertex);
		data.vertexBuffer->SetData(data.quadBufferBase, size);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawElements(data.vertexArray, data.quadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, whiteTexture, 0);
	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, unsigned int textureSlot)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, whiteColor, texture, textureSlot);
	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture>& texture, unsigned int textureSlot)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, texture, textureSlot);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(translation, rotation, scale, color, whiteTexture, 0);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture>& texture, unsigned int textureSlot)
	{
		DrawQuad(translation, rotation, scale, whiteColor, texture, textureSlot);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture>& texture, unsigned int textureSlot)
	{
		data.quadBufferOffset->position = translation;
		data.quadBufferOffset->color = color;
		data.quadBufferOffset++;

		data.quadBufferOffset->position = { translation.x, translation.y + scale.y, translation.z };
		data.quadBufferOffset->color = color;
		data.quadBufferOffset++;

		data.quadBufferOffset->position = { translation.x + scale.x, translation.y + scale.y, translation.z };
		data.quadBufferOffset->color = color;
		data.quadBufferOffset++;

		data.quadBufferOffset->position = { translation.x + scale.x, translation.y, translation.z };
		data.quadBufferOffset->color = color;
		data.quadBufferOffset++;

		data.quadIndexCount += 6;

		/*
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale, 1.0f));
		data.shader->SetMat4("u_model", model);

		data.shader->SetVec4("u_color", color);

		texture->Bind(textureSlot);
		data.shader->SetInt("u_texture", textureSlot);

		data.vertexArray->Bind();
		RenderCommand::DrawElements(data.vertexArray);
		*/
	}
}
