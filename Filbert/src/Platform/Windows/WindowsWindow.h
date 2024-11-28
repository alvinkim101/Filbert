#pragma once

#include "Filbert/Window.h"

struct GLFWwindow;

namespace Filbert
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow() override;

		void OnUpdate() override;

		void SetEventCallback(const EventCallbackFn& callback) override { m_data.callback = callback; }
		void SetVSync(bool enabled) override;

		bool IsVSyncEnabled() const override { return m_data.vSync; }
		unsigned int GetWidth() const override { return m_data.width; }
		unsigned int GetHeight() const override { return m_data.height; }

		void* GetNativeWindow() override { return m_window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFn callback;
		};

		WindowData m_data;
		GLFWwindow* m_window;
	};
}
