#include "Application.h"

namespace Filbert
{
	#define BIND_EVENT_FN(f) std::bind(&Application::f, this, std::placeholders::_1)

	Application::Application()
	{
		m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_running)
		{
			m_window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowCloseEvent));

		FB_CORE_TRACE("{}", event.Info());
	}

	bool Application::OnWindowCloseEvent(WindowCloseEvent& event)
	{
		m_running = false;
		return true;
	}
}
