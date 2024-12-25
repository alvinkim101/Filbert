#pragma once

#include "Filbert/Input/Input.h"

namespace Filbert
{
	class OpenGLInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int key) const override;
		bool IsMouseButtonPressedImpl(int button) const override;
		std::pair<float, float> GetMousePositionImpl() const override;
	};
}
