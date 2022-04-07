#pragma once

#include "Core.h"
#include "Window.h"
#include "ExitFlag.h"

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

#include "Timestep.h"

namespace Workbench
{
	class WORKBENCH_API Application
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

		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running;
		float m_LastFrameTime = 0.0f;

		static Application* s_Instance;
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}