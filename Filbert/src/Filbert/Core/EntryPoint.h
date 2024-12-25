#pragma once

extern Filbert::Application* Filbert::CreateApplication();

int main(int argc, char* argv[])
{
	Filbert::Log::Init();
	FB_TRACE("Welcome to Filbert Engine!");

	auto app = Filbert::CreateApplication();
	app->Run();
	delete app;
}
