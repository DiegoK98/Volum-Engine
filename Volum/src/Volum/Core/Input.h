#pragma once

#include "Volum/Core/Base.h"
#include "Volum/Core/KeyCodes.h"
#include "Volum/Core/MouseCodes.h"

namespace Volum
{
	class Input
	{
	protected:
		Input() = default;
	public:
		virtual ~Input() = default;

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;

		static bool IsKeyPressed(KeyCode key) { return s_instance->IsKeyPressedImpl(key); }
		static float IsMouseButtonPressed(MouseCode button) { return s_instance->IsMouseButtonPressedImpl(button); }
		static std::pair<float, float> GetMousePos() { return s_instance->GetMousePosImpl(); }

		static Scope<Input> Create();
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;
		virtual float IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Scope<Input> s_instance;
	};
}