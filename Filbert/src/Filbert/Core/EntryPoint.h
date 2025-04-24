#pragma once

extern Filbert::Application* Filbert::CreateApplication();

int main(int argc, char* argv[])
{
	Filbert::Log::Init();

	Filbert::Profiler::Begin("Init.json");
	auto app = Filbert::CreateApplication();
	Filbert::Profiler::End();

	Filbert::Profiler::Begin("Run.json");
	app->Run();
	Filbert::Profiler::End();

	Filbert::Profiler::Begin("Deinit.json");
	delete app;
	Filbert::Profiler::End();
}
