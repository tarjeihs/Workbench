#include "wbpch.h"
#include "Engine/Core/Log.h"

// Used for spdlog set_level function
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Workbench
{
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		
		s_EngineLogger = spdlog::stderr_color_mt("ENGINE");
		s_ClientLogger = spdlog::stderr_color_mt("CLIENT");
	
		s_EngineLogger->set_level(spdlog::level::trace);
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}