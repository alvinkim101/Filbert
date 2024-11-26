#include "WindowsWindow.h"
#include "Filbert/Events/ApplicationEvent.h"
#include "Filbert/Events/MouseEvent.h"
#include "Filbert/Events/KeyEvent.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Filbert
{
	namespace
	{
		bool GLFWInitialized = false;

		void GLFWErrorCallback(int error_code, const char* description)
		{
			FB_CORE_ERROR("glfwError errorcode = {}, description = {}", error_code, description);
		}
	}

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
		if (!GLFWInitialized)
		{
			int status = glfwInit();
			FB_CORE_ASSERT(status, "glfwInit failed");
			glfwSetErrorCallback(&GLFWErrorCallback);

			GLFWInitialized = true;
		}

		m_data.title = props.title;
		m_data.width = props.width;
		m_data.height = props.height;

		m_window = glfwCreateWindow(m_data.width, m_data.height, m_data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		int version = gladLoadGL(glfwGetProcAddress);
		FB_CORE_ASSERT(version, "gladLoadGL failed");

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		FB_CORE_INFO("WindowsWindow created with width {} and height {}", m_data.width, m_data.height);

		// Set callbacks
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowCloseEvent e;
				windowData->callback(e);
			}
		);

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* window, int focused)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				if (focused)
				{
					WindowFocusEvent e;
					windowData->callback(e);
				}
				else
				{
					WindowUnfocusEvent e;
					windowData->callback(e);
				}
			}
		);

		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				windowData->width = width;
				windowData->height = height;

				WindowResizeEvent e(width, height);
				windowData->callback(e);
			}
		);

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xpos, int ypos)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				WindowMoveEvent e(xpos, ypos);
				windowData->callback(e);
			}
		);

		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressEvent e(key, false);
						windowData->callback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressEvent e(key, true);
						windowData->callback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleaseEvent e(key);
						windowData->callback(e);
						break;
					}
				}
			}
		);

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressEvent e(button);
						windowData->callback(e);
						break;
					}
					case GLFW_REPEAT:
					{
						MouseButtonPressEvent e(button);
						windowData->callback(e);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleaseEvent e(button);
						windowData->callback(e);
						break;
					}
				}
			}
		);

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseMoveEvent e(xpos, ypos);
				windowData->callback(e);
			}
		);

		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset)
			{
				WindowData* windowData = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				MouseScrollEvent e(xoffset, yoffset);
				windowData->callback(e);
			}
		);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_window);
	}
}
