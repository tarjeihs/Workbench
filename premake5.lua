workspace "Workbench"
	architecture "x86_64"
	startproject "Editor"
	
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

	DependencyDir = {}
	DependencyDir["glfw"] = "Engine/vendor/glfw"
	DependencyDir["glad"] = "Engine/vendor/glad"
	DependencyDir["imgui"] = "Engine/vendor/imgui"
	DependencyDir["glm"] = "Engine/vendor/glm"
	DependencyDir["entt"] = "Engine/vendor/entt"
	
	DependencyIncludeDir = {}
	DependencyIncludeDir["glfw"] = "Engine/vendor/glfw/include"
	DependencyIncludeDir["glad"] = "Engine/vendor/glad/include"
	DependencyIncludeDir["imgui"] = "Engine/vendor/imgui"
	DependencyIncludeDir["glm"] = "Engine/vendor/glm"
	DependencyIncludeDir["entt"] = "Engine/vendor/entt/single_include"

	group "Vendor Dependency"
		project "glfw"
			location "%{DependencyDir.glfw}"
			kind "StaticLib"
			language "C"
			staticruntime "on"
		
			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
			defines 
			{
				"_CRT_SECURE_NO_WARNINGS"
			}
		
			files
			{
				"%{DependencyDir.glfw}/include/GLFW/glfw3.h",
				"%{DependencyDir.glfw}/include/GLFW/glfw3native.h",
				"%{DependencyDir.glfw}/src/glfw_config.h",
				"%{DependencyDir.glfw}/src/context.c",
				"%{DependencyDir.glfw}/src/init.c",
				"%{DependencyDir.glfw}/src/input.c",
				"%{DependencyDir.glfw}/src/monitor.c",
				"%{DependencyDir.glfw}/src/platform.c",
				"%{DependencyDir.glfw}/src/vulkan.c",
				"%{DependencyDir.glfw}/src/window.c",
				"%{DependencyDir.glfw}/src/null_init.c",
				"%{DependencyDir.glfw}/src/null_joystick.c",
				"%{DependencyDir.glfw}/src/null_monitor.c",
				"%{DependencyDir.glfw}/src/null_window.c"
			}
		
			filter "system:linux"
				systemversion "latest"
		
				pic "on"
				
				files
				{
					"%{DependencyDir.glfw}/src/x11_init.c",
					"%{DependencyDir.glfw}/src/x11_monitor.c",
					"%{DependencyDir.glfw}/src/x11_window.c",
					"%{DependencyDir.glfw}/src/xkb_unicode.c",
					"%{DependencyDir.glfw}/src/posix_time.c",
					"%{DependencyDir.glfw}/src/posix_thread.c",
					"%{DependencyDir.glfw}/src/glx_context.c",
					"%{DependencyDir.glfw}/src/egl_context.c",
					"%{DependencyDir.glfw}/src/osmesa_context.c",
					"%{DependencyDir.glfw}/src/linux_joystick.c"
				}
		
				defines
				{
					"_GLFW_X11"
				}
		
			filter "system:windows"
				systemversion "latest"
		
				files
				{
					"%{DependencyDir.glfw}/src/win32_init.c",
					"%{DependencyDir.glfw}/src/win32_joystick.c",
					"%{DependencyDir.glfw}/src/win32_module.c",
					"%{DependencyDir.glfw}/src/win32_monitor.c",
					"%{DependencyDir.glfw}/src/win32_time.c",
					"%{DependencyDir.glfw}/src/win32_thread.c",
					"%{DependencyDir.glfw}/src/win32_window.c",
					"%{DependencyDir.glfw}/src/wgl_context.c",
					"%{DependencyDir.glfw}/src/egl_context.c",
					"%{DependencyDir.glfw}/src/osmesa_context.c"
				}
		
				defines 
				{ 
					"_GLFW_WIN32",
				}
		
				links
				{
					"Dwmapi.lib"
				}
		
			filter "configurations:Debug"
				runtime "Debug"
				symbols "on"
		
			filter "configurations:Release"
				runtime "Release"
				optimize "on"
		
			filter "configurations:Dist"
				runtime "Release"
				optimize "on"
		        symbols "off"

		project "glad"
			location "%{DependencyDir.glad}"
			kind "StaticLib"
			language "C"
			staticruntime "on"
		
			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
			files 
			{
				"%{DependencyDir.glad}/include/glad/glad.h",
				"%{DependencyDir.glad}/include/khr/khrplatform.h",
				"%{DependencyDir.glad}/src/glad.c"
			}
		
			includedirs
			{
				"%{DependencyDir.glad}/include"
			}
		
			defines 
			{
				"_CRT_SECURE_NO_WARNINGS"
			}
			
			filter "system:windows"
				systemversion "latest"
		
			filter "configurations:Debug"
				runtime "Debug"
				symbols "on"
		
			filter "configurations:Release"
				runtime "Release"
				optimize "on"
		
			filter "configurations:Dist"
				runtime "Release"
				optimize "on"
		
		project "imgui"
			location "%{DependencyDir.imgui}"
			kind "StaticLib"
			language "C++"
			cppdialect "C++17"
		    staticruntime "on"
		
			targetdir ("bin/" .. outputdir .. "/%{prj.name}")
			objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
			files
			{
				"%{DependencyDir.imgui}/imconfig.h",
				"%{DependencyDir.imgui}/imgui.h",
				"%{DependencyDir.imgui}/imgui.cpp",
				"%{DependencyDir.imgui}/imgui_draw.cpp",
				"%{DependencyDir.imgui}/imgui_internal.h",
				"%{DependencyDir.imgui}/imgui_tables.cpp",
				"%{DependencyDir.imgui}/imgui_widgets.cpp",
				"%{DependencyDir.imgui}/imstb_rectpack.h",
				"%{DependencyDir.imgui}/imstb_textedit.h",
				"%{DependencyDir.imgui}/imstb_truetype.h",
				"%{DependencyDir.imgui}/imgui_demo.cpp"
			}
		
			filter "system:windows"
				systemversion "latest"
		
			filter "system:linux"
				systemversion "latest"	
				pic "On"
		
			filter "configurations:Debug"
				runtime "Debug"
				symbols "on"
		
			filter "configurations:Release"
				runtime "Release"
				optimize "on"
		
		    filter "configurations:Dist"
				runtime "Release"
				optimize "on"
		
	group ""
	
	project "Engine"
		location "Engine"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

		pchheader "wbpch.h"
		pchsource "Engine/src/wbpch.cpp"

		files 
		{ 
			"%{prj.name}/src/**.h", 
			"%{prj.name}/src/**.cpp" 
		}
		
		includedirs 
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{DependencyIncludeDir.glfw}",
			"%{DependencyIncludeDir.glad}",
			"%{DependencyIncludeDir.imgui}",
			"%{DependencyIncludeDir.glm}",
			"%{DependencyIncludeDir.entt}"
		}
		
		links 
		{
			"glfw",
			"glad",
			"imgui",
			"opengl32.lib"
		}
		
		defines 
		{
			"_CRT_SECURE_NO_WARNINGS",
			"GLFW_INCLUDE_NONE"
		}
		
		filter "system:windows"
			cppdialect "C++17"
			systemversion "latest"

			defines 
			{
				"WB_PLATFORM_WINDOWS",
				"WB_BUILD_DLL"
			}

		filter "configurations:Debug"
			defines "WB_DEBUG"
			runtime "Debug"
			symbols "on"
		
		filter "configurations:Release"
			defines "WB_RELEASE"
			runtime "Release"
			optimize "on"
		
		filter "configurations:Dist"
			defines "WB_DIST"
			runtime "Release"
			optimize "on"

	project "Editor"
		location "Editor"
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
			"Engine/vendor/spdlog/include",
			"Engine/src",
			"Engine/vendor",
			"%{DependencyIncludeDir.glm}",
			"%{DependencyIncludeDir.entt}"
		}

		links
		{
			"Engine"
		}

		defines 
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

		filter "system:windows"
			cppdialect "C++17"
			staticruntime "on"
			systemversion "latest"

			defines
			{
				"WB_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "WB_DEBUG"
			runtime "Debug"
			symbols "on"
	
		filter "configurations:Release"
			defines "WB_RELEASE"
			runtime "Release"
			optimize "on"
	
		filter "configurations:Dist"
			defines "WB_DIST"
			runtime "Release"
			optimize "on"