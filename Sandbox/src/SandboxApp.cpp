#include <Filbert.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Filbert::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer")
	{
		glm::vec3 vertices[] =
		{
			glm::vec3(-0.5f, -0.5f, 0.0f),
			glm::vec3(0.0f, 0.5f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.0f)
		};

		unsigned int indices[] =
		{
			0, 1, 2
		};

		Filbert::BufferLayout layout =
		{
			{ "coordinates", Filbert::ShaderDataType::Float3 }
		};

		std::string vertexSource = R"(
			#version 460 core

			uniform mat4 model;
			uniform mat4 viewProjection;

			layout (location = 0) in vec3 inPosition;

			void main()
			{
				mat4 modelViewProjection = viewProjection * model;
				gl_Position = modelViewProjection * vec4(inPosition, 1.0f);
			}
		)";

		std::string fragmentSource = R"(
			#version 460 core

			uniform vec3 color;
			
			out vec4 outColor;

			void main()
			{
				outColor = vec4(color, 1.0f);
			} 
		)";

		std::shared_ptr<Filbert::VertexBuffer> vertexBuffer;
		std::shared_ptr<Filbert::ElementBuffer> elementBuffer;
		vertexBuffer.reset(Filbert::VertexBuffer::Create(vertices, sizeof(vertices)));
		elementBuffer.reset(Filbert::ElementBuffer::Create(indices, sizeof(indices)));
		vertexBuffer->SetLayout(layout);

		m_shader.reset(Filbert::Shader::Create(vertexSource, fragmentSource));
		m_vertexArray.reset(Filbert::VertexArray::Create());

		m_vertexArray->AddVertexBuffer(vertexBuffer);
		m_vertexArray->SetElementBuffer(elementBuffer);
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

		// Object color
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_color));
		ImGui::End();
		m_shader->UploadUniform("color", m_color);

		Filbert::Renderer::Submit(m_shader, m_vertexArray, "viewProjection", m_objectRotation, "model");

		Filbert::Renderer::EndScene();
	}

	void OnEvent(Filbert::Event& event) override
	{

	}

private:
	std::shared_ptr<Filbert::VertexArray> m_vertexArray;
	std::shared_ptr<Filbert::Shader> m_shader;

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
