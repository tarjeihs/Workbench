#include "wbpch.h"

#include "Application.h"
#include <gl/GL.h>

namespace Workbench
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(WB_BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& event)
	{
		//EventDispatcher dispatcher(event);
		//dispatcher.Dispatch()

		WB_ENGINE_INFO("{0}", event);
	}

	void Application::Run()
	{
		while (m_Running) 
		{
			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}