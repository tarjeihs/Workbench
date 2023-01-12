#pragma once

#include "Workbench.h"

#include "Engine/Renderer/PerspectiveCamera.h"
#include "Engine/Renderer/EditorCamera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

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
		bool OnWindowResize(WindowResizeEvent& event);
	private:
		Ref<Scene> m_Scene;

		Entity m_CameraEntity;
		Entity m_SquareEntity;

		EditorCamera m_EditorCamera = EditorCamera(45, 1280 / 720, 0.01f, 1000.0f);
		PerspectiveCamera m_SceneCamera;

		enum class SceneCameraState { Interlude = 0, Runtime = 1, Simulate = 2 };
		enum class SceneUpdateState { UpdateInterlude = 0, UpdateRuntime = 1, UpdateSimulate = 2 };

		SceneCameraState m_SceneCameraState = SceneCameraState::Interlude;
		SceneUpdateState m_SceneUpdateState = SceneUpdateState::UpdateInterlude;
		
		std::pair<uint32_t, uint32_t> m_ViewportSize = { 1280, 720 };
	};
}