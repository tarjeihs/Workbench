project "Glad"
    kind "StaticLib"
    language "C"

    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

    files 
    {
		"include/glad/glad.h",
		"include/khr/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

    filter { "system:windows", "configurations:Debug" }
        runtime "Debug"
        symbols "On"
        buildoptions "/MDd"

    filter { "system:windows", "configurations:Release" }
        runtime "Release"
        symbols "On"
        buildoptions "/MD"

    filter { "system:windows", "configurations:Dist" }
        runtime "Release"
        buildoptions "/MD"
        optimize "On"