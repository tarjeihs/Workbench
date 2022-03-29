#include "wbpch.h"

#include "Application.h"

#include "Event/KeyEvent.h"
#include "Log.h"

namespace Workbench
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		KeyPressedEvent event(10, 10);
		WB_INFO(event);

		while (true) 
		{
			
		}
	}
}