workspace "Wire"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Wire"
    location "Wire"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include",
        "Wire/src"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "WR_PLATFORM_WINDOWS",
            "WR_BUILD_DLL"
        }

        postbuildcommands
        {
            ("if not exist ..\\bin\\" .. outputdir .. "\\Sandbox mkdir ..\\bin\\" .. outputdir .. "\\Sandbox\\"),
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines "WR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "WR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "WR_DIST"
        optimize "On"


project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "Wire/vendor/spdlog/include",
        "Wire/src"
    }

    links
    {
        "Wire"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "WR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "WR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "WR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "WR_DIST"
        optimize "On"