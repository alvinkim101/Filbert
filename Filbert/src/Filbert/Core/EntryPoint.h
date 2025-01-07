#pragma once

extern Filbert::Application* Filbert::CreateApplication();

int main(int argc, char* argv[])
{
	Filbert::Log::Init();

	auto app = Filbert::CreateApplication();

	Filbert::Profiler::Begin("Run.json");
	app->Run();
	Filbert::Profiler::End();

	delete app;
}
