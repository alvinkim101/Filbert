#include "LayerStack.h"

enum
{
	Layers = 0,
	Overlays = 1
};

namespace Filbert
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_joinedLayers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers[Layers].push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto i = std::find(m_layers[Layers].begin(), m_layers[Layers].end(), layer);

		if (i != m_layers[Layers].end())
		{
			m_layers[Layers].erase(i);
			layer->OnDetach();
		}
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers[Overlays].push_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto i = std::find(m_layers[Overlays].begin(), m_layers[Overlays].end(), overlay);

		if (i != m_layers[Overlays].end())
		{
			m_layers[Overlays].erase(i);
			overlay->OnDetach();
		}
	}
}
