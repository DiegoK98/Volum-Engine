#pragma once

#include "Volum/Core/Core.h"

#ifdef VLM_PLATFORM_WINDOWS

//extern Volum::Application* Volum::CreateApplication();

int main(int argc, char** argv)
{
	Volum::Log::Init();

	VLM_PROFILE_BEGIN_SESSION("Startup", "profiler/VolumProfiler-Startup.json");
	auto app = Volum::CreateApplication();
	VLM_PROFILE_END_SESSION();

	VLM_PROFILE_BEGIN_SESSION("Runtime", "profiler/VolumProfiler-Runtime.json");
	app->Run();
	VLM_PROFILE_END_SESSION();

	VLM_PROFILE_BEGIN_SESSION("Shutdown", "profiler/VolumProfiler-Shutdown.json");
	delete app;
	VLM_PROFILE_END_SESSION();
}

#endif