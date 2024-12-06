#include <Filbert.h>

#include <glm/vec3.hpp>

class ExampleLayer : public Filbert::Layer
{
	struct Vertex
	{
		glm::vec3 coordinates;
		glm::vec3 color;
	};

public:
	ExampleLayer() : Layer("ExampleLayer")
	{
		Vertex vertices[] =
		{
			{ glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) },
			{ glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f) }
		};

		unsigned int indices[] =
		{
			0, 1, 2
		};

		Filbert::BufferLayout layout =
		{
			{ "coordinates", Filbert::ShaderDataType::Float3 },
			{ "color", Filbert::ShaderDataType::Float3 }
		};

		std::string vertexSource = R"(
			#version 460 core

			layout (location = 0) in vec3 aPosition;
			layout (location = 1) in vec3 aColor;
			
			out vec3 bColor;

			void main()
			{
				gl_Position = vec4(aPosition, 1.0f);
				bColor = aColor;
			}
		)";

		std::string fragmentSource = R"(
			#version 460 core

			in vec3 bColor;
			
			out vec4 fragmentColor;

			void main()
			{
				fragmentColor = vec4(bColor, 1.0f);
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

	void OnUpdate() override
	{
		if (Filbert::Input::IsKeyPressed(FB_KEY_F))
		{
			FB_TRACE("Pay Respects");
		}
	}

	void OnRender() override
	{
		Filbert::Renderer::BeginScene();
		Filbert::Renderer::Submit(m_shader, m_vertexArray);
		Filbert::Renderer::EndScene();
	}

	void OnEvent(Filbert::Event& event) override
	{
		FB_TRACE("{} - {}", m_debugName, event.Info());
	}

private:
	std::shared_ptr<Filbert::VertexArray> m_vertexArray;
	std::shared_ptr<Filbert::Shader> m_shader;
};

class Sandbox : public Filbert::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Filbert::ImGuiLayer());
	}

	virtual ~Sandbox()
	{

	}
};

Filbert::Application* Filbert::CreateApplication()
{
	return new Sandbox();
}
