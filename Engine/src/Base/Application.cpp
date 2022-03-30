#include "wbpch.h"

#include "Application.h"

#include <glad/glad.h>

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

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::Run()
	{
		while (m_Running)
		{
			for (Layer* layer : m_LayerStack) { layer->OnUpdate(); }

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(WB_BIND_EVENT_FN(OnWindowClose));

		WB_ENGINE_TRACE("{0}", event);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.IsHandled) { break; }
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;

		return m_Running;
	}
}