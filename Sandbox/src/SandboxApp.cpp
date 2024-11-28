#include <Filbert.h>

class ExampleLayer : public Filbert::Layer
{
public:
	ExampleLayer() : Layer("ExampleLayer")
	{

	}

	void OnUpdate() override
	{

	}

	void OnEvent(Filbert::Event& event) override
	{
		FB_TRACE("{} - {}", m_debugName, event.Info());
	}
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
