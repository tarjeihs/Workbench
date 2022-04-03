project "Sandbox"
location "Sandbox"
kind "ConsoleApp"
language "C++"
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
    "Engine/vendor"
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
    runtime "Debug"
    buildoptions "/MDd"
    symbols "on"

filter "configurations:Release"
    defines "WB_RELEASE"
    runtime "Release"
    buildoptions "/MD"
    optimize "on"

filter "configurations:Dist"
    defines "WB_DIST"
    runtime "Release"
    buildoptions "/MD"
    optimize "on"