#pragma once

#include "Core.h"
#include "LayerStack.h"
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

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

	private:
		bool OnWindowCloseEvent(WindowCloseEvent& event);

		std::unique_ptr<Window> m_window{ Window::Create() };
		LayerStack m_layerStack;
		bool m_running = true;
	};

	// To be defined in the client
	Application* CreateApplication();
}
