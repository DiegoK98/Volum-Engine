workspace "Volum"
    architecture "x64"
    startproject "Example"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Volum/vendor/GLFW/include"
IncludeDir["Glad"] = "Volum/vendor/Glad/include"
IncludeDir["ImGui"] = "Volum/vendor/ImGui"

group "Dependencies"
    include "Volum/vendor/GLFW"
    include "Volum/vendor/Glad"
    include "Volum/vendor/ImGui"

group ""


project "Volum"
    location "Volum"
    kind "SharedLib"
    language "C++"
    staticruntime "Off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "vlmpch.h"
    pchsource "Volum/src/vlmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}"
    }

    links
    {
        "GLFW",
        "Glad",
        "ImGui",
        "opengl32.lib"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "VLM_PLATFORM_WINDOWS",
            "VLM_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Example/\"")
        }

    filter "configurations:Debug"
        defines "VLM_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "VLM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "VLM_DIST"
        runtime "Release"
        optimize "On"

project "Example"
    location "Example"
    kind "ConsoleApp"
    language "C++"
    staticruntime "Off"

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
        "Volum/src"
    }

    links
    {
        "Volum"
    }

    filter "system:windows"
        cppdialect "C++20"
        systemversion "latest"

        defines
        {
            "VLM_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "VLM_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "VLM_RELEASE"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "VLM_DIST"
        runtime "Release"
        optimize "On"