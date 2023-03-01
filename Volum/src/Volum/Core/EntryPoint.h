#pragma once

#include "Volum/Core/Core.h"

#ifdef VLM_PLATFORM_WINDOWS

//extern Volum::Application* Volum::CreateApplication();

int main(int argc, char** argv)
{
	Volum::Log::Init();

	auto app = Volum::CreateApplication();
	app->Run();
	delete app;
}

#endif