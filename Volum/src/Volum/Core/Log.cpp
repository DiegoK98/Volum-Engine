#include "vlmpch.h"

#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Volum
{
	Ref<spdlog::logger> Log::s_coreLogger;
	Ref<spdlog::logger> Log::s_clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_coreLogger = spdlog::stdout_color_mt("VOLUM");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("APP");
		s_clientLogger->set_level(spdlog::level::trace);

		VLM_CORE_INFO("Log initialized");
	}
}