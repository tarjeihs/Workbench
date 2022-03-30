#include "wbpch.h"

#include "Application.h"

namespace Workbench
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Workbench::Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running) 
		{
			m_Window->OnUpdate();
		}
	}
}