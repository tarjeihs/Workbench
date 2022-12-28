#pragma once

#ifdef WB_LIB_DLL
	#ifdef WB_BUILD_DLL
		#define WORKBENCH_API __declspec(dllexport)
	#else
		#define WORKBENCH_API __declspec(dllimport)
	#endif
#endif

#ifdef WB_DEBUG
	#if defined(WB_PLATFORM_WINDOWS)
		#define WB_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform targeted to Windows only as of now."
	#endif
	#define WB_ENABLE_ASSERTS
#else
	#define WB_DEBUGBREAK()
#endif

#define WB_EXPAND_MACRO(x) x
#define WB_STRINGIFY_MACRO(x) #x

#define WB_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#include "Engine/Core/Log.h"
#include "Engine/Core/Assert.h"