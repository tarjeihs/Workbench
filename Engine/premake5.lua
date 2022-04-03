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

defines 
{
    "_CRT_SECURE_NO_WARNINGS",
    "GLFW_INCLUDE_NONE",
    "IMGUI_IMPL_OPENGL_LOADER_CUSTOM"
}

includedirs 
{
    "%{prj.name}/src",
    "%{prj.name}/vendor/spdlog/include",
    "%{IncludeDir.GLFW}",
    "%{IncludeDir.Glad}",
    "%{IncludeDir.ImGui}"
}

links 
{
    "Glad",
    "GLFW",
    "ImGui",
    "opengl32.lib"
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
