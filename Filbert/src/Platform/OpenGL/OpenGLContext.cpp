#include "OpenGLContext.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Filbert
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_window(window)
	{
		FB_CORE_ASSERT(window, "OpenGLContext window is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_window);
		int version = gladLoadGL(glfwGetProcAddress);
		FB_CORE_ASSERT(version, "gladLoadGL failed");

		FB_CORE_INFO("OpenGL: vendor {}, renderer {}, version {}", (const char *)glGetString(GL_VENDOR), (const char *)glGetString(GL_RENDERER), (const char *)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_window);
	}
}
