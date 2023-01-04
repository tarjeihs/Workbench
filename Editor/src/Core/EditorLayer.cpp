#include "EditorLayer.h"

// Temporary
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

namespace Workbench
{
	EditorLayer::EditorLayer()
		: Layer("Editor")
	{
	}

	void EditorLayer::OnAttach()
	{
		m_EditorScene = std::make_unique<Scene>();
		m_EditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		m_EditorCamera.OnUpdate(ts);

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		m_EditorScene->OnUpdateEditor(ts, m_EditorCamera);
	}

	void EditorLayer::OnImGuiRender(Timestep ts)
	{
		static bool showDemoWindow = true;
		ImGui::Begin("Metrics", &showDemoWindow);
		ImGui::Text("Last frame time: %f ms (%f)", ts.GetMilliseconds(), 1000.0f / ts.GetMilliseconds());
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(WB_BIND_EVENT_FN(OnWindowResize));
		m_EditorCamera.OnEvent(event);
	}

	// Clean up mess here

	bool EditorLayer::OnWindowResize(WindowResizeEvent& event)
	{
		m_EditorCamera.SetViewport(event.GetWidth(), event.GetHeight());
		m_EditorScene->OnViewportResize(event.GetWidth(), event.GetHeight());
		return false;
	}

	void EditorLayer::OnScenePlay()
	{
		m_SceneState = SceneState::Play;
	}

	void EditorLayer::OnSceneStop()
	{
		m_SceneState = SceneState::Edit;
	}
}