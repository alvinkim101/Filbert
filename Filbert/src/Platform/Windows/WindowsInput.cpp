#include "WindowsInput.h"
#include "Filbert/Application.h"

#include <GLFW/glfw3.h>

namespace Filbert
{
	Input* Input::s_input = new WindowsInput();

	namespace
	{
		inline GLFWwindow* GetGLFWwindow()
		{
			return static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		}
	}

	bool WindowsInput::IsKeyPressedImpl(int key) const
	{
		GLFWwindow* window = GetGLFWwindow();

		return glfwGetKey(window, key) == GLFW_PRESS; // GLFW_REPEAT is only reported to the callback
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow* window = GetGLFWwindow();

		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{
		GLFWwindow* window = GetGLFWwindow();
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);
		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}
}
