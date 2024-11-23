#include "Application.h"
#include "Log.h"

namespace Filbert
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		auto event = WindowResizeEvent(1920, 1080);
		FB_INFO(event.Info());
	}
}
