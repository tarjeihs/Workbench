#pragma once

#ifdef WB_PLATFORM_WINDOWS
	#ifdef WB_BUILD_DLL
		#define WORKBENCH_API __declspec(dllexport)
	#else
		#define WORKBENCH_API __declspec(dllimport)
	#endif
#endif
