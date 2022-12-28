#pragma once

#include "Core.h"

#include "spdlog/spdlog.h"

// Ignores all warnings raised inside external header files
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Workbench
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define WB_ENGINE_TRACE(...) ::Workbench::Log::GetEngineLogger()->trace(__VA_ARGS__)
#define WB_ENGINE_INFO(...)  ::Workbench::Log::GetEngineLogger()->info(__VA_ARGS__)
#define WB_ENGINE_WARN(...)  ::Workbench::Log::GetEngineLogger()->warn(__VA_ARGS__)
#define WB_ENGINE_ERROR(...) ::Workbench::Log::GetEngineLogger()->error(__VA_ARGS__)

#define WB_CLIENT_TRACE(...) ::Workbench::Log::GetClientLogger()->trace(__VA_ARGS__)
#define WB_CLIENT_INFO(...)  ::Workbench::Log::GetClientLogger()->info(__VA_ARGS__)
#define WB_CLIENT_WARN(...)  ::Workbench::Log::GetClientLogger()->warn(__VA_ARGS__)
#define WB_CLIENT_ERROR(...) ::Workbench::Log::GetClientLogger()->error(__VA_ARGS__)