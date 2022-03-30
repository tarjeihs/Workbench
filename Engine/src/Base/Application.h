#pragma once

#include "Core.h"
#include "Window.h"

namespace Workbench
{
	class WORKBENCH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running;
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}