#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Filbert
{
	class FILBERT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		void OnEvent(Event& e);
		bool OnWindowCloseEvent(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window{ Window::Create() };
		bool m_running = true;
	};

	// To be defined in the client
	Application* CreateApplication();
}
