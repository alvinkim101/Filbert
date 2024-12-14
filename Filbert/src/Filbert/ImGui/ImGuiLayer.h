#pragma once

namespace Filbert
{
	class ImGuiLayer
	{
	public:
		static void Initialize();
		static void Deinitialize();

		static void NewFrame();
		static void Render();
	};
}
