#pragma once

#include "Core.h"

namespace Filbert
{
	class Input
	{
	public:
		static bool IsKeyPressed(int key) { return s_input->IsKeyPressedImpl(key); }
		static bool IsMouseButtonPressed(int key) { return s_input->IsMouseButtonPressedImpl(key); }
		static std::pair<float, float> GetMousePosition() { return s_input->GetMousePositionImpl(); };

	protected:
		virtual bool IsKeyPressedImpl(int key) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual std::pair<float, float> GetMousePositionImpl() const = 0;

	private:
		static Input* s_input;
	};
}
