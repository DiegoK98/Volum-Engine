#pragma once

#include <memory>

#include "Volum/Core/PlatformDetection.h"

#ifdef VLM_DEBUG
	#if defined(VLM_PLATFORM_WINDOWS)
		#define VLM_DEBUGBREAK() __debugbreak()
	#elif defined(VLM_PLATFORM_LINUX)
		#include <signal.h>
		#define VLM_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define VLM_ENABLE_ASSERTS
#else
	#define VLM_DEBUGBREAK()
#endif

#ifdef VLM_ENABLE_ASSERTS
	#define VLM_ASSERT(x, ...) { if(!(x)) { VLM_ERROR("Assertion Failed: {0}", __VA_ARGS__); VLM_DEBUGBREAK(); } }
	#define VLM_CORE_ASSERT(x, ...) { if(!(x)) { VLM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); VLM_DEBUGBREAK(); } }
#else
	#define VLM_ASSERT(x, ...)
	#define VLM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define VLM_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define VLM_RENDERER_3D 1 // 0 = Renderer2D, 1 = Renderer3D

namespace Volum
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
