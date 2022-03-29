workspace "Workbench"
    architecture "x64"
    startproject "Sandbox"
    
    configurations 
    { 
        "Debug", 
        "Release", 
        "Dist" 
    }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "Engine/vendor/GLFW/include"
    include "Engine/vendor/GLFW"

    project "Engine"
        location "Engine"
        kind "SharedLib"
        language "C++"

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
            "%{prj.name}/vendor/spdlog/include",
            "%{prj.name}/src",
            "%{IncludeDir.GLFW}"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines 
            {
                "WB_PLATFORM_WINDOWS",
                "WB_BUILD_DLL"
            }
            
            postbuildcommands
            {
                ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
            }

        filter "configurations:Debug"
            defines "WB_DEBUG"
            symbols "On"
        
        filter "configurations:Release"
            defines "WB_RELEASE"
            optimize "On"
        
        filter "configurations:Dist"
            defines "WB_DIST"
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
            "%{prj.name}/src/**.cpp" 
        }

        includedirs
        {
            "Engine/vendor/spdlog/include",
            "Engine/src"
        }

        links
        {
            "Engine"
        }

        filter "system:windows"
            cppdialect "C++17"
            staticruntime "On"
            systemversion "latest"

            defines 
            {
                "WB_PLATFORM_WINDOWS"
            }

        filter "configurations:Debug"
            defines "WB_DEBUG"
            symbols "On"
    
        filter "configurations:Release"
            defines "WB_RELEASE"
            optimize "On"
    
        filter "configurations:Dist"
            defines "WB_DIST"
            optimize "On"