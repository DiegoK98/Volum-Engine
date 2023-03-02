#include "vlmpch.h"

#include "Volum/Core/Window.h"

#ifdef VLM_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace Volum
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef VLM_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		VLM_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}