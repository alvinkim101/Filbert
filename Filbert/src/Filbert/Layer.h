#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Filbert
{
	class FILBERT_API Layer
	{
	public:
		Layer(const std::string& debugName = "Layer") : m_debugName(debugName) {};
		virtual ~Layer() {};

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetDebugName() const { return m_debugName; }

	protected:
		std::string m_debugName;
	};
}
