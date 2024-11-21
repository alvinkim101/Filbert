#pragma once

#ifdef FB_PLATFORM_WINDOWS

extern Filbert::Application* Filbert::CreateApplication();

int main(int argc, char* argv[])
{
	auto app = Filbert::CreateApplication();
	app->Run();
	delete app;
}

#endif
