#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Core/Log.h"

#include <filesystem>

#ifdef WB_ENABLE_ASSERTS
	#define WB_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { WB##type##ERROR(msg, __VA_ARGS__); WB_DEBUGBREAK(); } }
	#define WB_INTERNAL_ASSERT_WITH_MSG(type, check, ...) WB_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define WB_INTERNAL_ASSERT_NO_MSG(type, check) WB_INTERNAL_ASSERT_IMLP(type, check, "Assertion failed {0} at {1}:{2}", WB_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
	
	#define WB_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define WB_INTERNAL_ASSERT_GET_MACRO(...) WB_EXPAND_MACRO(WB_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, WB_INTERNAL_ASSERT_WITH_MSG, WB_INTERNAL_ASSERT_NO_MSG))

	#define WB_CLIENT_ASSERT(...) WB_EXPAND_MACRO(WB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CLIENT_, __VA_ARGS__))
	#define WB_ENGINE_ASSERT(...) WB_EXPAND_MACRO(WB_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_ENGINE_, __VA_ARGS__))
#else
	#define WB_CLIENT_ASSERT(...)
	#define WB_ENGINE_ASSERT(...)
#endif