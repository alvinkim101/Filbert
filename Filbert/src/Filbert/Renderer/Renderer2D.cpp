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
			int32_t textureSlot;
		};

		struct Renderer2DData
		{
			// If exceed max, another draw call is needed
			// # of draw calls = (quads / maxQuads + 1) + 1
			static constexpr unsigned int maxQuads = 10000;
			static constexpr unsigned int maxVertices = maxQuads * 4;
			static constexpr unsigned int maxIndices = maxQuads * 6;
			static constexpr unsigned int maxTextures = 32; // TODO: Query graphics API e.g. GL_MAX_TEXTURE_IMAGE_UNITS

			std::shared_ptr<VertexArray> vertexArray;
			std::shared_ptr<VertexBuffer> vertexBuffer;
			std::shared_ptr<Shader> shader;

			unsigned int quadIndexCount = 0;
			QuadVertex* quadBufferBase = nullptr;
			QuadVertex* quadBufferOffset = nullptr;

			std::unordered_map<std::shared_ptr<Texture2D>, int32_t> textures;

			glm::vec4 vertexPositions[4]{ // Centered with side length 1
				{ -0.5f, -0.5f, 0.0f, 1.0f },
				{ -0.5f, 0.5f, 0.0f, 1.0f },
				{ 0.5f, 0.5f, 0.0f, 1.0f },
				{ 0.5f, -0.5f, 0.0f, 1.0f }
			};

			Renderer2D::Stats stats;
		};

		Renderer2DData data;

		// Used when color or texture is not specified
		std::shared_ptr<Texture2D> whiteTexture;
		const glm::vec4 whiteColor = glm::vec4(1.0f);

		constexpr glm::vec3 zAxis(0.0f, 0.0f, 1.0f);
	}

	void Renderer2D::Initialize()
	{
		whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		whiteTexture->SetData(&whiteTextureData, sizeof(whiteTextureData));
		data.textures[whiteTexture] = 0;

		// Vertex buffer
		BufferLayout quadLayout =
		{
			{ "position", ShaderDataType::Float3 },
			{ "color", ShaderDataType::Float4 },
			{ "textureCoordinates", ShaderDataType::Float2 },
			{ "textureSlot", ShaderDataType::Int }
		};
		data.quadBufferBase = new QuadVertex[Renderer2DData::maxVertices];
		data.vertexBuffer = VertexBuffer::Create(Renderer2DData::maxVertices * sizeof(QuadVertex));
		data.vertexBuffer->SetLayout(quadLayout);
		data.quadBufferOffset = data.quadBufferBase;

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
		data.shader = Shader::Create("Renderer2D", "assets/shaders/ColorTexture.glsl"); // TODO: Fix updated assets not being used if Sandbox is not built

		// Textures
		int slots[data.maxTextures];
		std::iota(slots, slots + data.maxTextures, 0);
		data.shader->SetInts("u_textures", slots, data.maxTextures);
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
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		unsigned int size = static_cast<unsigned int>((data.quadBufferOffset - data.quadBufferBase) * sizeof(QuadVertex));
		data.vertexBuffer->SetData(data.quadBufferBase, size);

		for (const auto& [texture, slot] : data.textures)
		{
			texture->Bind(slot);
		}

		RenderCommand::DrawElements(data.vertexArray, data.quadIndexCount);

		data.textures.clear(); // Maybe cache?
		data.quadIndexCount = 0;
		data.quadBufferOffset = data.quadBufferBase;
		data.textures[whiteTexture] = 0;

		data.stats.drawCalls++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, whiteTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, whiteColor, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color)
	{
		DrawQuad(translation, rotation, scale, color, whiteTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const std::shared_ptr<Texture2D>& texture)
	{
		DrawQuad(translation, rotation, scale, whiteColor, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec4& color, const std::shared_ptr<Texture2D>& texture)
	{
		if (data.quadIndexCount == data.maxIndices)
		{
			Flush();
		}

		int32_t textureSlot;
		if (data.textures.count(texture))
		{
			textureSlot = data.textures[texture];
		}
		else
		{
			textureSlot = static_cast<int32_t>(data.textures.size());
			data.textures[texture] = textureSlot;
		}

		glm::mat4 model(1.0f);
		model = glm::translate(model, translation)
			* glm::rotate(model, glm::radians(rotation), zAxis)
			* glm::scale(model, { scale, 1.0f });

		data.quadBufferOffset->position = model * data.vertexPositions[0];
		data.quadBufferOffset->color = color;
		data.quadBufferOffset->textureCoordinates = { 0.0f, 0.0f };
		data.quadBufferOffset->textureSlot = textureSlot;
		data.quadBufferOffset++;

		data.quadBufferOffset->position = model * data.vertexPositions[1];
		data.quadBufferOffset->color = color;
		data.quadBufferOffset->textureCoordinates = { 0.0f, 1.0f };
		data.quadBufferOffset->textureSlot = textureSlot;
		data.quadBufferOffset++;

		data.quadBufferOffset->position = model * data.vertexPositions[2];
		data.quadBufferOffset->color = color;
		data.quadBufferOffset->textureCoordinates = { 1.0f, 1.0f };
		data.quadBufferOffset->textureSlot = textureSlot;
		data.quadBufferOffset++;

		data.quadBufferOffset->position = model * data.vertexPositions[3];
		data.quadBufferOffset->color = color;
		data.quadBufferOffset->textureCoordinates = { 1.0f, 0.0f };
		data.quadBufferOffset->textureSlot = textureSlot;
		data.quadBufferOffset++;

		data.quadIndexCount += 6;

		data.stats.quadCount++;
	}

	Renderer2D::Stats Renderer2D::GetStats()
	{
		return data.stats;
	}

	void Renderer2D::ResetStats()
	{
		memset(&data.stats, 0, sizeof(Renderer2D::Stats));
	}
}
