#pragma once

namespace Volum
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}
// Codes from glfw3.h
#define VLM_MOUSE_BUTTON_1         ::Volum::Mouse::Button0
#define VLM_MOUSE_BUTTON_2         ::Volum::Mouse::Button1
#define VLM_MOUSE_BUTTON_3         ::Volum::Mouse::Button2
#define VLM_MOUSE_BUTTON_4         ::Volum::Mouse::Button3
#define VLM_MOUSE_BUTTON_5         ::Volum::Mouse::Button4
#define VLM_MOUSE_BUTTON_6         ::Volum::Mouse::Button5
#define VLM_MOUSE_BUTTON_7         ::Volum::Mouse::Button6
#define VLM_MOUSE_BUTTON_8         ::Volum::Mouse::Button7
#define VLM_MOUSE_BUTTON_LAST      ::Volum::Mouse::ButtonLast
#define VLM_MOUSE_BUTTON_LEFT      ::Volum::Mouse::ButtonLeft
#define VLM_MOUSE_BUTTON_RIGHT     ::Volum::Mouse::ButtonRight
#define VLM_MOUSE_BUTTON_MIDDLE    ::Volum::Mouse::ButtonMiddle