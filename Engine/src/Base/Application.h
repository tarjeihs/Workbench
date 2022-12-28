#pragma once

#include "Core.h"
#include "Window.h"
#include "ExitFlag.h"

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Timestep.h"

namespace Workbench
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();

		void OnEvent(Event& event);

		void Exit(const ExitFlag& exitFlag);

		inline Window& GetWindow() { return *m_Window; }
		inline Timestep& GetTimestep() { return m_Timestep; }

		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Minimized;

		bool m_Running = true;
		float m_LastFrameTime = 0.0f;
		Timestep m_Timestep;

		static Application* s_Instance;
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}