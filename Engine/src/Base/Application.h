#pragma once

#include "Core.h"
#include "Event/Event.h"
#include "Window.h"

namespace Workbench
{
	class WORKBENCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}