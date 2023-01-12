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
		m_Scene = CreateRef<Scene>();

		m_CameraEntity = m_Scene->CreateEntity("Camera");
		m_CameraEntity.AddComponent<CameraComponent>().Bind<PerspectiveCamera>();

		m_SquareEntity = m_Scene->CreateEntity("Box");
		m_SquareEntity.AddComponent<SpriteRendererComponent>();
	}

	void EditorLayer::OnDetach()
	{
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		m_Scene->UpdateNativeScriptComponent(ts);

		switch (m_SceneUpdateState)
		{
			case SceneUpdateState::UpdateInterlude: 
			{ 
				m_EditorCamera.OnUpdate(ts); 		
				m_Scene->DrawQuad(m_EditorCamera); 
				break;
			}
			WB_CLIENT_ASSERT(false, "Variable of SceneUpdateState is out of scope");
		}
	}

	void EditorLayer::OnImGuiRender(Timestep ts)
	{
		static bool showDemoWindow = true;
		ImGui::Begin("Metrics", &showDemoWindow);
		ImGui::Text("Last frame time: %f ms (%f)", ts.GetMilliseconds(), 1000.0f / ts.GetMilliseconds());
		ImGui::Text("Camera Entity Position X: %f", m_CameraEntity.GetComponent<TransformComponent>().Translation[0]);
		ImGui::Text("Camera Entity Position Y: %f", m_CameraEntity.GetComponent<TransformComponent>().Translation[1]);
		ImGui::Text("Camera Entity Position Z: %f", m_CameraEntity.GetComponent<TransformComponent>().Translation[2]);
		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(WB_BIND_EVENT_FN(OnWindowResize));
	}

	bool EditorLayer::OnWindowResize(WindowResizeEvent& event)
	{
		m_Scene->OnViewportResize(event.GetWidth(), event.GetHeight());

		return false;
	}
}