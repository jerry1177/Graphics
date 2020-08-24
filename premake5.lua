workspace "Graphics"
	architecture "x64"
	startproject "OpenGL"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "OpenGL/vendor/GLFW/include"
IncludeDir["Glad"] = "OpenGL/vendor/Glad/include"
IncludeDir["ImGui"] = "OpenGL/vendor/imgui"
IncludeDir["glm"] = "OpenGL/vendor/glm"
IncludeDir["stb_image"] = "OpenGL/vendor/stb_image"

include "OpenGL/vendor/GLFW"
include "OpenGL/vendor/GLAD"

project "OpenGL"
	location "OpenGL"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "hzpch.h"
	pchsource "OpenGL/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp"
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

	links {
		"GLFW",
		"GLAD"
	}
	


	filter "system:windows"
		
		systemversion "latest"

		defines
		{
			"_GLFW_WIN32",
			"_WIND32",
			"_WIND64",
			"HZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
		}
		

	filter "configurations:Debug"
		defines "HZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HZ_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"

	filter "configurations:Dist"
		defines "HZ_DIST"
		runtime "Release"
		optimize "on"
		symbols "on"