#pragma once

#include "Volum/Core/Input.h"

namespace Volum
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool isKeyPressedImpl(int keycode) override;
		virtual float isMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};	
}