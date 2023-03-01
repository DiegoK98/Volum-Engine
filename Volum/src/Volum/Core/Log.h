#pragma once

#include "Volum/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Volum
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	private:
		static Ref<spdlog::logger> s_coreLogger;
		static Ref<spdlog::logger> s_clientLogger;
	};
}

// Core log macros
#define VLM_CORE_TRACE(...)      ::Volum::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define VLM_CORE_INFO(...)       ::Volum::Log::GetCoreLogger()->info(__VA_ARGS__)
#define VLM_CORE_WARN(...)       ::Volum::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define VLM_CORE_ERROR(...)      ::Volum::Log::GetCoreLogger()->error(__VA_ARGS__)
#define VLM_CORE_CRITICAL(...)   ::Volum::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define VLM_TRACE(...)           ::Volum::Log::GetClientLogger()->trace(__VA_ARGS__)
#define VLM_INFO(...)            ::Volum::Log::GetClientLogger()->info(__VA_ARGS__)
#define VLM_WARN(...)            ::Volum::Log::GetClientLogger()->warn(__VA_ARGS__)
#define VLM_ERROR(...)           ::Volum::Log::GetClientLogger()->error(__VA_ARGS__)
#define VLM_CRITICAL(...)        ::Volum::Log::GetClientLogger()->critical(__VA_ARGS__)