#pragma once

#ifndef VLM_PLATFORM_WINDOWS
	#error Volum only supports Windows!
#endif

#ifdef VLM_DEBUG
	#define VLM_ENABLE_ASSERTS
#endif

#ifdef VLM_ENABLE_ASSERTS
	#define VLM_ASSERT(x, ...) { if(!(x)) { VLM_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define VLM_CORE_ASSERT(x, ...) { if(!(x)) { VLM_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define VLM_ASSERT(x, ...)
	#define VLM_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define VLM_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)