#include "Application.h"
#include "ImGui/ImGuiLayer.h"

namespace Filbert
{
	#define BIND_EVENT_FN(f) std::bind(&Application::f, this, std::placeholders::_1)

	Application* Application::s_application = nullptr;

	Application::Application()
	{
		FB_CORE_ASSERT(!s_application, "More than one application created");
		s_application = this;

		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		ImGuiLayer::Initialize();
	}

	Application::~Application()
	{
		ImGuiLayer::Deinitialize();
	}

	void Application::Run()
	{
		while (m_running)
		{
			ProcessInput();
			Update();
			Render();
		}
	}

	void Application::ProcessInput()
	{
		m_window->ProcessInput();
	}

	void Application::Update()
	{
		float currentTime = m_window->GetTime();
		float deltaTime = currentTime - m_previousUpdateTime;
		m_previousUpdateTime = currentTime;

		for (Layer* layer : m_layerStack)
		{
			layer->OnUpdate(deltaTime);
		}
	}

	void Application::Render()
	{
		m_window->Clear();

		ImGuiLayer::NewFrame();

		for (Layer* layer : m_layerStack)
		{
			layer->OnRender();
		}

		ImGuiLayer::Render();

		m_window->SwapBuffers();
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

		for (Layer* layer : std::ranges::reverse_view(m_layerStack))
		{
			if (event.handled)
			{
				break;
			}

			layer->OnEvent(event);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_layerStack.PopOverlay(overlay);
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		m_running = false;
		event.handled = true;
		return true;
	}
}
