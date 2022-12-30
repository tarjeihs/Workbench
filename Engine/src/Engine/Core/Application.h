#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Core/Window.h"

#include "Engine/Core/LayerStack.h"
#include "Engine/Core/Timestep.h"

#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/Scene/Scene.h"

namespace Workbench
{
	class Application
	{
	public:
		enum ExitFlag : uint8_t { None = 0, Error = 1 };

		Application(const std::string& name);
		virtual ~Application();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		void Run();
		void Exit(const ExitFlag& exitFlag);

		void OnEvent(Event& event);

		inline Window& GetWindow() { return *m_Window; }
		inline Scene& GetScene() { return *m_Scene; }

		static inline Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		std::unique_ptr<Window> m_Window;
		std::shared_ptr<Scene> m_Scene;
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