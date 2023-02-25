#pragma once

#include "Core.h"

namespace Volum
{
	class VOLUM_API Input
	{
	public:
		inline static bool isKeyPressed(int keycode) { return s_instance->isKeyPressedImpl(keycode); }
		inline static float isMouseButtonPressed(int button) { return s_instance->isMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePos() { return s_instance->GetMousePosImpl(); }

	protected:
		virtual bool isKeyPressedImpl(int keycode) = 0;
		virtual float isMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_instance;
	};
}