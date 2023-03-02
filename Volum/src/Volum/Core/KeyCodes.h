#pragma once

namespace Volum
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// Codes from glfw3.h
#define VLM_KEY_SPACE              ::Volum::Key::Space
#define VLM_KEY_APOSTROPHE         ::Volum::Key::Apostrophe  /* ' */
#define VLM_KEY_COMMA              ::Volum::Key::Comma  /* , */
#define VLM_KEY_MINUS              ::Volum::Key::Minus  /* - */
#define VLM_KEY_PERIOD             ::Volum::Key::Perid  /* . */
#define VLM_KEY_SLASH              ::Volum::Key::Slash  /* / */
#define VLM_KEY_0                  ::Volum::Key::D0
#define VLM_KEY_1                  ::Volum::Key::D1
#define VLM_KEY_2                  ::Volum::Key::D2
#define VLM_KEY_3                  ::Volum::Key::D3
#define VLM_KEY_4                  ::Volum::Key::D4
#define VLM_KEY_5                  ::Volum::Key::D5
#define VLM_KEY_6                  ::Volum::Key::D6
#define VLM_KEY_7                  ::Volum::Key::D7
#define VLM_KEY_8                  ::Volum::Key::D8
#define VLM_KEY_9                  ::Volum::Key::D9
#define VLM_KEY_SEMICOLON          ::Volum::Key::Semicolon  /* ; */
#define VLM_KEY_EQUAL              ::Volum::Key::Equal  /* = */
#define VLM_KEY_A                  ::Volum::Key::A
#define VLM_KEY_B                  ::Volum::Key::B
#define VLM_KEY_C                  ::Volum::Key::C
#define VLM_KEY_D                  ::Volum::Key::D
#define VLM_KEY_E                  ::Volum::Key::E
#define VLM_KEY_F                  ::Volum::Key::F
#define VLM_KEY_G                  ::Volum::Key::G
#define VLM_KEY_H                  ::Volum::Key::H
#define VLM_KEY_I                  ::Volum::Key::I
#define VLM_KEY_J                  ::Volum::Key::J
#define VLM_KEY_K                  ::Volum::Key::K
#define VLM_KEY_L                  ::Volum::Key::L
#define VLM_KEY_M                  ::Volum::Key::M
#define VLM_KEY_N                  ::Volum::Key::N
#define VLM_KEY_O                  ::Volum::Key::O
#define VLM_KEY_P                  ::Volum::Key::P
#define VLM_KEY_Q                  ::Volum::Key::Q
#define VLM_KEY_R                  ::Volum::Key::R
#define VLM_KEY_S                  ::Volum::Key::S
#define VLM_KEY_T                  ::Volum::Key::T
#define VLM_KEY_U                  ::Volum::Key::U
#define VLM_KEY_V                  ::Volum::Key::V
#define VLM_KEY_W                  ::Volum::Key::W
#define VLM_KEY_X                  ::Volum::Key::X
#define VLM_KEY_Y                  ::Volum::Key::Y
#define VLM_KEY_Z                  ::Volum::Key::Z
#define VLM_KEY_LEFT_BRACKET       ::Volum::Key::LeftBracket /* [ */
#define VLM_KEY_BACKSLASH          ::Volum::Key::Backslash /* \ */
#define VLM_KEY_RIGHT_BRACKET      ::Volum::Key::RightBracket /* ] */
#define VLM_KEY_GRAVE_ACCENT       ::Volum::Key::GraveAccent /* ` */
#define VLM_KEY_WORLD_1            ::Volum::Key::World1 /* non-US #1 */
#define VLM_KEY_WORLD_2            ::Volum::Key::World2 /* non-US #2 */

/* Function keys */
#define VLM_KEY_ESCAPE             ::Volum::Key::Escape
#define VLM_KEY_ENTER              ::Volum::Key::Enter
#define VLM_KEY_TAB                ::Volum::Key::Tab
#define VLM_KEY_BACKSPACE          ::Volum::Key::Backspace
#define VLM_KEY_INSERT             ::Volum::Key::Insert
#define VLM_KEY_DELETE             ::Volum::Key::Delete
#define VLM_KEY_RIGHT              ::Volum::Key::Right
#define VLM_KEY_LEFT               ::Volum::Key::Left
#define VLM_KEY_DOWN               ::Volum::Key::Down
#define VLM_KEY_UP                 ::Volum::Key::Up
#define VLM_KEY_PAGE_UP            ::Volum::Key::PageUp
#define VLM_KEY_PAGE_DOWN          ::Volum::Key::PageDown
#define VLM_KEY_HOME               ::Volum::Key::Home
#define VLM_KEY_END                ::Volum::Key::End
#define VLM_KEY_CAPS_LOCK          ::Volum::Key::CapsLock
#define VLM_KEY_SCROLL_LOCK        ::Volum::Key::ScrollLock
#define VLM_KEY_NUM_LOCK           ::Volum::Key::NumLock
#define VLM_KEY_PRINT_SCREEN       ::Volum::Key::PrintScreen
#define VLM_KEY_PAUSE              ::Volum::Key::Pause
#define VLM_KEY_F1                 ::Volum::Key::F1
#define VLM_KEY_F2                 ::Volum::Key::F2
#define VLM_KEY_F3                 ::Volum::Key::F3
#define VLM_KEY_F4                 ::Volum::Key::F4
#define VLM_KEY_F5                 ::Volum::Key::F5
#define VLM_KEY_F6                 ::Volum::Key::F6
#define VLM_KEY_F7                 ::Volum::Key::F7
#define VLM_KEY_F8                 ::Volum::Key::F8
#define VLM_KEY_F9                 ::Volum::Key::F9
#define VLM_KEY_F10                ::Volum::Key::F10
#define VLM_KEY_F11                ::Volum::Key::F11
#define VLM_KEY_F12                ::Volum::Key::F12
#define VLM_KEY_F13                ::Volum::Key::F13
#define VLM_KEY_F14                ::Volum::Key::F14
#define VLM_KEY_F15                ::Volum::Key::F15
#define VLM_KEY_F16                ::Volum::Key::F16
#define VLM_KEY_F17                ::Volum::Key::F17
#define VLM_KEY_F18                ::Volum::Key::F18
#define VLM_KEY_F19                ::Volum::Key::F19
#define VLM_KEY_F20                ::Volum::Key::F20
#define VLM_KEY_F21                ::Volum::Key::F21
#define VLM_KEY_F22                ::Volum::Key::F22
#define VLM_KEY_F23                ::Volum::Key::F23
#define VLM_KEY_F24                ::Volum::Key::F24
#define VLM_KEY_F25                ::Volum::Key::F25

/* Keypad */
#define VLM_KEY_KP_0               ::Volum::Key::KP0
#define VLM_KEY_KP_1               ::Volum::Key::KP1
#define VLM_KEY_KP_2               ::Volum::Key::KP2
#define VLM_KEY_KP_3               ::Volum::Key::KP3
#define VLM_KEY_KP_4               ::Volum::Key::KP4
#define VLM_KEY_KP_5               ::Volum::Key::KP5
#define VLM_KEY_KP_6               ::Volum::Key::KP6
#define VLM_KEY_KP_7               ::Volum::Key::KP7
#define VLM_KEY_KP_8               ::Volum::Key::KP8
#define VLM_KEY_KP_9               ::Volum::Key::KP9
#define VLM_KEY_KP_DECIMAL         ::Volum::Key::KPDecimal
#define VLM_KEY_KP_DIVIDE          ::Volum::Key::KPDivide
#define VLM_KEY_KP_MULTIPLY        ::Volum::Key::KPMultiply
#define VLM_KEY_KP_SUBTRACT        ::Volum::Key::KPSubtract
#define VLM_KEY_KP_ADD             ::Volum::Key::KPAdd
#define VLM_KEY_KP_ENTER           ::Volum::Key::KPEnter
#define VLM_KEY_KP_EQUAL           ::Volum::Key::KPEqual

#define VLM_KEY_LEFT_SHIFT         ::Volum::Key::LeftShift
#define VLM_KEY_LEFT_CONTROL       ::Volum::Key::LeftControl
#define VLM_KEY_LEFT_ALT           ::Volum::Key::LeftAlt
#define VLM_KEY_LEFT_SUPER         ::Volum::Key::LeftSuper
#define VLM_KEY_RIGHT_SHIFT        ::Volum::Key::RightShift
#define VLM_KEY_RIGHT_CONTROL      ::Volum::Key::RightControl
#define VLM_KEY_RIGHT_ALT          ::Volum::Key::RightAlt
#define VLM_KEY_RIGHT_SUPER        ::Volum::Key::RightSuper
#define VLM_KEY_MENU               ::Volum::Key::Menu