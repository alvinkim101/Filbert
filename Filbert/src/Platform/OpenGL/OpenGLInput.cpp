#include "OpenGLInput.h"
#include "Filbert/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Filbert
{
	namespace
	{
		inline GLFWwindow* GetGLFWwindow()
		{
			return static_cast<GLFWwindow*>(Application::GetApplication().GetWindow().GetNativeWindow());
		}
	}

	bool OpenGLInput::IsKeyPressedImpl(int key) const
	{
		GLFWwindow* window = GetGLFWwindow();

		return glfwGetKey(window, key) == GLFW_PRESS; // GLFW_REPEAT is only reported to the callback
	}

	bool OpenGLInput::IsMouseButtonPressedImpl(int button) const
	{
		GLFWwindow* window = GetGLFWwindow();

		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	std::pair<float, float> OpenGLInput::GetMousePositionImpl() const
	{
		GLFWwindow* window = GetGLFWwindow();
		double xpos, ypos;

		glfwGetCursorPos(window, &xpos, &ypos);
		return { static_cast<float>(xpos), static_cast<float>(ypos) };
	}
}
