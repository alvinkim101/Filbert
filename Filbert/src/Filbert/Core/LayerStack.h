#pragma once

#include "Core.h"
#include "Layer.h"

namespace Filbert
{
	class LayerStack
	{
	public:
		~LayerStack();

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		auto begin() { return m_joinedLayers.begin(); }
		auto end() { return m_joinedLayers.end(); }

	private:
		// Would have preferred to use two separate vectors but std::ranges::concat_view requires C++26
		std::array<std::vector<Layer*>, 2> m_layers;
		std::ranges::join_view<std::ranges::ref_view<std::array<std::vector<Filbert::Layer*>, 2>>> m_joinedLayers { m_layers };
	};
}
