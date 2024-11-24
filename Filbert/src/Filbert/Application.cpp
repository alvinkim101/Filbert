#include "Application.h"

namespace Filbert
{
	Application::Application()
	{

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
}
