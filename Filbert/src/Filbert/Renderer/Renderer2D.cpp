#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Filbert
{
	namespace
	{
		struct Renderer2DStorage
		{
			std::shared_ptr<VertexArray> vertexArray;
			std::shared_ptr<Shader> shader;
		};

		std::unique_ptr<Renderer2DStorage> storage;
	}

	void Renderer2D::Initialize()
	{
		storage = std::make_unique<Renderer2DStorage>();

		glm::vec3 squareVertices[] =
		{
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(-0.5f, 0.5f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.0f)
		};

		/*Vertex squareVertices[] =
		{
			Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f))
		};*/

		unsigned int squareIndices[] =
		{
			0, 1, 2,
			0, 3, 2
		};

		BufferLayout squareLayout =
		{
			{ "position", ShaderDataType::Float3 },
			//{ "textureCoordinates", ShaderDataType::Float2 }
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		std::shared_ptr<ElementBuffer> elementBuffer;
		vertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		elementBuffer = ElementBuffer::Create(squareIndices, sizeof(squareIndices));
		vertexBuffer->SetLayout(squareLayout);

		storage->vertexArray = VertexArray::Create();
		storage->vertexArray->AddVertexBuffer(vertexBuffer);
		storage->vertexArray->SetElementBuffer(elementBuffer);

		storage->shader = Shader::Create("Color", "assets/shaders/Color.glsl");

		/*auto shader = m_shaderLibrary.Load("Texture", "assets/shaders/Texture.glsl");
		m_texture = Texture2D::Create("assets/textures/reddit.png");
		shader->SetInt("u_texture", 0);*/
	}

	void Renderer2D::Deinitialize()
	{
		storage.reset();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		storage->shader->Bind();
		storage->shader->SetMat4("u_viewProjection", camera.GetViewProjection());
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color)
	{
		DrawQuad(glm::vec3(translation, 0.0f), rotation, scale, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& translation, const float rotation, const glm::vec2& scale, const glm::vec3& color)
	{
		storage->shader->Bind();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, translation);
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(scale, 1.0f));

		storage->shader->SetMat4("u_model", model);
		storage->shader->SetVec3("u_color", color);

		storage->vertexArray->Bind();
		RenderCommand::DrawElements(storage->vertexArray);
	}
}
