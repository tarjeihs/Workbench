#pragma once

#include "Core.h"
#include "Window.h"

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

// TEMPORARY
#include "Renderer/VertexArray.h"
#include "Renderer/Buffer.h"
#include "Renderer/Shader.h"
#include "Renderer/OrthographicCamera.h"

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

		inline Window& GetWindow() { return *m_Window; }

		void Exit(int exitCode = 0);
	public:
		static inline Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		bool m_Running;
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}