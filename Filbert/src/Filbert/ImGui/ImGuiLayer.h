#pragma once

#include <Filbert/Core/Layer.h>

namespace Filbert
{
	class ImGuiLayer : public Layer
	{
	public:
		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnEvent(Event& event) override;

		static void NewFrame();
		static void Render();

	private:
		static void Initialize();
		static void Deinitialize();
	};
}
