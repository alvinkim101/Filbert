#pragma once

#include "Filbert/Layer.h"

namespace Filbert
{
	class FILBERT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnRender() override;
		void OnEvent(Event& event) override;

		void Begin();
		void End();

	private:

	};
}
