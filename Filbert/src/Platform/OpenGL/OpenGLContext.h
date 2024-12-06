#pragma once

#include "Filbert/Renderer/Context.h"

struct GLFWwindow;

namespace Filbert
{
	class OpenGLContext : public Context
	{
	public:
		OpenGLContext(GLFWwindow* window);
		void Init() override;
		void SwapBuffers() override;

	private:
		GLFWwindow* m_window;
	};
}
