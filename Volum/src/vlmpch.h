#pragma once

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

#include "Volum/Core/Log.h"

#include "Volum/Debug/Instrumentor.h"

#ifdef VLM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif