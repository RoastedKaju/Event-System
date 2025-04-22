workspace "Event-System"
	architecture "x64"
	startproject "EventSystem"

	configurations
	{
		"Debug",
		"Release"
	}

project "EventSystem"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir "Binaries/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	objdir "Intermediate/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}

	filter "configurations:Debug"
		symbols "On"

	filter "configurations:Release"
		optimize "On"