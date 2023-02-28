workspace "Volum"
    architecture "x64"
    startproject "Sandbox"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Volum/vendor/GLFW/include"
IncludeDir["Glad"] = "Volum/vendor/Glad/include"
IncludeDir["ImGui"] = "Volum/vendor/ImGui"
IncludeDir["glm"] = "Volum/vendor/glm"
IncludeDir["stb_image"] = "Volum/vendor/stb_image"

group "Dependencies"
    include "Volum/vendor/GLFW"
    include "Volum/vendor/Glad"
    include "Volum/vendor/ImGui"

group ""


project "Volum"
    location "Volum"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "vlmpch.h"
    pchsource "Volum/src/vlmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "VLM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "VLM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "VLM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "VLM_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Volum/vendor/spdlog/include",
        "Volum/src",
        "Volum/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Volum"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "VLM_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "VLM_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "VLM_DIST"
        runtime "Release"
        optimize "on"