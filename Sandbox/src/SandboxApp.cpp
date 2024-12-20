#include <Filbert.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Filbert::Layer
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 textureCoordinates;
	};

public:
	ExampleLayer() : Layer("ExampleLayer")
	{
		Vertex squareVertices[] = // Clockwise starting from bottom left
		{
			Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec2(0.0f, 0.0f)),
			Vertex(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)),
			Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f))
		};

		unsigned int squareIndices[] =
		{
			0, 1, 2,
			0, 3, 2
		};

		Filbert::BufferLayout squareLayout =
		{
			{ "position", Filbert::ShaderDataType::Float3 },
			{ "textureCoordinates", Filbert::ShaderDataType::Float2 }
		};

		std::shared_ptr<Filbert::VertexBuffer> vertexBuffer;
		std::shared_ptr<Filbert::ElementBuffer> elementBuffer;
		vertexBuffer.reset(Filbert::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		elementBuffer.reset(Filbert::ElementBuffer::Create(squareIndices, sizeof(squareIndices)));
		vertexBuffer->SetLayout(squareLayout);

		auto shader = m_shaderLibrary.Load("Texture", "assets/shaders/Texture.glsl");

		m_vertexArray.reset(Filbert::VertexArray::Create());
		m_vertexArray->AddVertexBuffer(vertexBuffer);
		m_vertexArray->SetElementBuffer(elementBuffer);

		m_texture.reset(Filbert::Texture2D::Create("assets/textures/reddit.png"));
		shader->UploadUniform("u_texture", 0);
	}

	void OnUpdate(float deltaTime) override
	{
		// Camera translation
		float distance = m_cameraTranslateSpeed * deltaTime;

		if (Filbert::Input::IsKeyPressed(FB_KEY_W))
		{
			m_camera.Translate(glm::vec3(0, 0, distance));
		}

		if (Filbert::Input::IsKeyPressed(FB_KEY_S))
		{
			m_camera.Translate(glm::vec3(0, 0, -distance));
		}

		if (Filbert::Input::IsKeyPressed(FB_KEY_A))
		{
			m_camera.Translate(glm::vec3(-distance, 0, 0));
		}

		if (Filbert::Input::IsKeyPressed(FB_KEY_D))
		{
			m_camera.Translate(glm::vec3(distance, 0, 0));
		}

		// Object rotation
		float degrees = m_objectRotationSpeed * deltaTime;
		m_objectRotation = glm::rotate(m_objectRotation, glm::radians(degrees), m_objectRotationAxis);
	}

	void OnRender() override
	{
		Filbert::Renderer::BeginScene(m_camera);

		/*ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
		ImGui::End();
		m_shader->UploadUniform("u_color", m_color);*/

		m_texture->Bind();

		auto shader = m_shaderLibrary.Get("Texture");
		Filbert::Renderer::Submit(shader, m_vertexArray, "u_viewProjection", m_objectRotation, "u_model");

		Filbert::Renderer::EndScene();
	}

	void OnEvent(Filbert::Event& event) override
	{

	}

private:
	Filbert::ShaderLibrary m_shaderLibrary;
	std::shared_ptr<Filbert::VertexArray> m_vertexArray;
	std::shared_ptr<Filbert::Texture2D> m_texture;

	Filbert::PerspectiveCamera m_camera;
	float m_cameraTranslateSpeed = 1.0f;

	glm::mat4 m_objectRotation = glm::mat4(1.0f);
	glm::vec3 m_objectRotationAxis = glm::vec3{ 0, 0, 1.0f };
	float m_objectRotationSpeed = 180.0f; // degrees per sec

	glm::vec3 m_color = { 1.0f, 0.0f, 0.0f };
};

class Sandbox : public Filbert::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox()
	{

	}
};

Filbert::Application* Filbert::CreateApplication()
{
	return new Sandbox();
}
