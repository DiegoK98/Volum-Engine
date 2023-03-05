#pragma once

#include "Volum/Core/Base.h"
#include "Volum/Core/KeyCodes.h"
#include "Volum/Core/MouseCodes.h"

namespace Volum
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static float IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePos();
	};
}