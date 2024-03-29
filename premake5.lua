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

    IncludeDir = {}
    IncludeDir["glfw"] = "Engine/vendor/glfw/include"
    IncludeDir["glad"] = "Engine/vendor/glad/include"
    IncludeDir["imgui"] = "Engine/vendor/imgui"
    IncludeDir["glm"] = "Engine/vendor/glm"
    IncludeDir["entt"] = "Engine/vendor/entt/single_include"
    
    group "Vendor Directory"
        include "Engine/vendor/glfw"
        include "Engine/vendor/glad"
        include "Engine/vendor/imgui"
    group ""
    
    project "Engine"
        location "Engine"
        kind "StaticLib"
        language "C++"
        cppdialect "C++17"
        staticruntime "on"

        targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
        objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

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
            "%{IncludeDir.glfw}",
            "%{IncludeDir.glad}",
            "%{IncludeDir.imgui}",
            "%{IncludeDir.glm}",
            "%{IncludeDir.entt}"
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
            "%{IncludeDir.glm}",
            "%{IncludeDir.entt}"
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