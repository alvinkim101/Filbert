#include "Application.h"

namespace Filbert
{
	#define BIND_EVENT_FN(f) std::bind(&Application::f, this, std::placeholders::_1)

	Application* Application::s_application = nullptr;

	Application::Application()
	{
		FB_ASSERT(!s_application, "More than one application created");
		s_application = this;
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_running)
		{
			for (Layer* layer : m_layerStack)
			{
				layer->OnUpdate();
			}

			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

		for (Layer* layer : std::ranges::reverse_view(m_layerStack))
		{
			layer->OnEvent(event);

			if (event.handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PopLayer(Layer* layer)
	{
		m_layerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_layerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		m_running = false;
		return true;
	}
}
