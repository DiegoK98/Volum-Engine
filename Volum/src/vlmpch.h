#pragma once

#include "Volum/Core/PlatformDetection.h"

#ifdef VLM_PLATFORM_WINDOWS
	#ifndef NOMINMAX
		// See github.com/skypjack/entt/wiki/Frequently-Asked-Questions#warning-c4003-the-min-the-max-and-the-macro
		#define NOMINMAX
	#endif
#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Volum/Core/Base.h"

#include "Volum/Core/Log.h"

#include "Volum/Debug/Instrumentor.h"

#ifdef VLM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
