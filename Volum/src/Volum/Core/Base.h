#pragma once

#include <memory>

// Platform detection
#ifdef _WIN32
	#ifdef _WIN64
		#define VLM_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define VLM_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define VLM_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
	/* We also have to check __ANDROID__ before __linux__
	* since android is based on the linux kernel
	* it has __linux__ defined */
#elif defined(__ANDROID__)
	#define VLM_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define VLM_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif

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

#define VLM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

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