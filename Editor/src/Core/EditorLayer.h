#pragma once

#include "Workbench.h"

#include "Engine/Renderer/EditorCamera.h"

namespace Workbench
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender(Timestep ts) override;
		virtual void OnEvent(Event& event) override;
	private:
		void OnScenePlay();
		void OnSceneStop();

		bool OnWindowResize(WindowResizeEvent& event);
		
		enum class SceneState { Edit = 0, Play = 1 };
	private:
		SceneState m_SceneState = SceneState::Edit;
		std::unique_ptr<Scene> m_EditorScene = nullptr;
		EditorCamera m_EditorCamera;
	};
}