#pragma once

#ifdef WB_PLATFORM_WINDOWS
	#ifdef WB_BUILD_DLL
		#define WORKBENCH_API __declspec(dllexport)
	#else
		#define WORKBENCH_API __declspec(dllimport)
	#endif
#endif

#ifdef WB_ENABLE_ASSERTS
	#define WB_ENGINE_ASSERT(x, ...) { if(!(x)) { WB_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define WB_CLIENT_ASSERT(x, ...) { if(!(x)) { WB_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define WB_ENGINE_ASSERT(x, ...);
	#define WB_CLIENT_ASSERT(x, ...);
#endif
