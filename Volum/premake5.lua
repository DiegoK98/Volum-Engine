project "Volum"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "vlmpch.h"
    pchsource "src/vlmpch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp",
        "vendor/stb_image/**.h",
        "vendor/stb_image/**.cpp",
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "GLFW_INCLUDE_NONE"
    }

    includedirs
    {
        "src",
        "vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.entt}"
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
