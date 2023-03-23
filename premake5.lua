include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Volum"
    architecture "x86_64"
    startproject "Volum-Engine"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    solution_items
	{
		".editorconfig"
	}

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Volum/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Volum/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Volum/vendor/ImGui"
IncludeDir["glm"] = "%{wks.location}/Volum/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Volum/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Volum/vendor/entt/include"

group "Dependencies"
    include "vendor/premake"
    include "Volum/vendor/GLFW"
    include "Volum/vendor/Glad"
    include "Volum/vendor/ImGui"

group ""

include "Volum"

group "Volum Apps"
    include "Volum-Editor"
    include "Sandbox"