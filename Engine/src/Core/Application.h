#pragma once

#include "Core.h"

namespace Workbench
{
	class WORKBENCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}