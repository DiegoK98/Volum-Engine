project "Volum-Editor"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/Volum/vendor/spdlog/include",
        "%{wks.location}/Volum/src",
        "%{wks.location}/Volum/vendor",
        "%{IncludeDir.glm}",
        "%{IncludeDir.entt}"
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