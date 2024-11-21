#pragma once

#include "Core.h"

namespace Filbert
{
	class FILBERT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in the client
	Application* CreateApplication();
}
