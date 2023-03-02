#pragma once

#include "Volum/Core/Input.h"

namespace Volum
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) override;
		virtual float IsMouseButtonPressedImpl(MouseCode button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};	
}