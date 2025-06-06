#pragma once

#include "Core.h"
#include "Filbert/Events/Event.h"

namespace Filbert
{
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer") : m_debugName(debugName) {};
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetDebugName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}
