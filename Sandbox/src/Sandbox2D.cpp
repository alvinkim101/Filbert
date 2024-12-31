#include "Sandbox2D.h"

#include <Filbert/Core/EntryPoint.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

void Sandbox2D::OnAttach()
{
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

	Filbert::BufferLayout squareLayout =
	{
		{ "position", Filbert::ShaderDataType::Float3 },
		//{ "textureCoordinates", Filbert::ShaderDataType::Float2 }
	};

	std::shared_ptr<Filbert::VertexBuffer> vertexBuffer;
	std::shared_ptr<Filbert::ElementBuffer> elementBuffer;
	vertexBuffer = Filbert::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	elementBuffer = Filbert::ElementBuffer::Create(squareIndices, sizeof(squareIndices));
	vertexBuffer->SetLayout(squareLayout);

	m_vertexArray = Filbert::VertexArray::Create();
	m_vertexArray->AddVertexBuffer(vertexBuffer);
	m_vertexArray->SetElementBuffer(elementBuffer);

	m_shaderLibrary.Load("Color", "assets/shaders/Color.glsl");

	/*auto shader = m_shaderLibrary.Load("Texture", "assets/shaders/Texture.glsl");
	m_texture = Filbert::Texture2D::Create("assets/textures/reddit.png");
	shader->UploadUniform("u_texture", 0);*/
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(float deltaTime)
{
	// Camera controller update
	m_cameraController.OnUpdate(deltaTime);

	// Object rotation
	float degrees = m_objectRotationSpeed * deltaTime;
	m_objectRotation = glm::rotate(m_objectRotation, glm::radians(degrees), m_objectRotationAxis);
}

void Sandbox2D::OnRender()
{
	Filbert::Renderer::BeginScene(m_cameraController.GetCamera());

	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
	ImGui::End();

	auto shader = m_shaderLibrary.Get("Color");
	shader->UploadUniform("u_color", m_color);

	/*m_texture->Bind();
	auto shader = m_shaderLibrary.Get("Texture");*/

	Filbert::Renderer::Submit(shader, m_vertexArray, "u_viewProjection", m_objectRotation, "u_model");

	Filbert::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Filbert::Event& event)
{
	m_cameraController.OnEvent(event);
}
