#include "WindowsWindow.h"

#include <GLFW/glfw3.h>

namespace Filbert
{
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled);
		m_data.vSync = enabled;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		int status = glfwInit();
		FB_CORE_ASSERT(status, "glfwInit failed");

		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		FB_CORE_INFO("WindowsWindow created with width {} and height {}", m_data.width, m_data.height);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}
}
