#pragma once

#include "Core.h"
#include "Window.h"

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

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
	public:
		static inline Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> m_Window;
		bool m_Running;

		LayerStack m_LayerStack;
		ImGuiLayer* m_ImGuiLayer;

		uint32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
	};

	// Will be defined through Sandbox
	Application* CreateApplication();
}