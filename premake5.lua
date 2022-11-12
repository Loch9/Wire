workspace "Wire"
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

IncludeDir = {}
IncludeDir["GLFW"] = "Wire/vendor/GLFW/include"
IncludeDir["Glad"] = "Wire/vendor/Glad/include"
IncludeDir["ImGui"] = "Wire/vendor/imgui"
IncludeDir["glm"] = "Wire/vendor/glm"
IncludeDir["stb_image"] = "Wire/vendor/stb_image"

group "Dependencies"
	include "Wire/vendor/GLFW"
	include "Wire/vendor/Glad"
	include "Wire/vendor/imgui"
group ""

project "Wire"
	location "Wire"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "wrpch.h"
	pchsource "Wire/src/wrpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
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
		"%{IncludeDir.stb_image}"

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
			"WR_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "WR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WR_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
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
		"Wire/vendor/spdlog/include",
		"Wire/src",
		"Wire/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Wire"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "WR_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "WR_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "WR_DIST"
		runtime "Release"
		optimize "on"
