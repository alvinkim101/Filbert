#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

namespace Filbert
{
	class Application
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

		Window& GetWindow() { return *m_window; }

		static Application& GetApplication() { FB_CORE_ASSERT(s_application, "Application not initialized"); return *s_application; }

	private:
		inline void ProcessInput();
		inline void Update();
		inline void Render();

		bool OnWindowCloseEvent(WindowCloseEvent& event);

		static Application* s_application;
		std::unique_ptr<Window> m_window{ Window::Create() };
		LayerStack m_layerStack;
		bool m_running = true;
	};

	// To be defined in the client
	Application* CreateApplication();
}
