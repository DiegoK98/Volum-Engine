#include "vlmpch.h"
#include "Volum/Core/Input.h"

#ifdef VLM_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace Volum {

	Scope<Input> Input::s_instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef VLM_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		VLM_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}