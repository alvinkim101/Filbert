#pragma once

#include "Filbert/Core/Window.h"

struct GLFWwindow;

namespace Filbert
{
	class OpenGLWindow : public Window
	{
	public:
		OpenGLWindow(const WindowProps& props);
		~OpenGLWindow() override;

		void ProcessInput() override;
		void Clear() override;
		void SwapBuffers() override;

		void SetEventCallback(const EventCallbackFn& callback) override { m_data.callback = callback; }
		void SetVSync(bool enabled) override;

		bool IsVSyncEnabled() const override { return m_data.vSync; }
		unsigned int GetWidth() const override { return m_data.width; }
		unsigned int GetHeight() const override { return m_data.height; }

		float GetTime() const override;

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
