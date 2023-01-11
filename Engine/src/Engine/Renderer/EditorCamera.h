#pragma once

#include "Engine/Renderer/ProjectionCamera.h"

#include "Engine/Event/MouseEvent.h"

namespace Workbench
{
	class EditorCamera : public ProjectionCamera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& event);

		inline float GetDistance() const { return m_Distance; }
		inline void SetDistance(float distance) { m_Distance = distance; }

		inline void SetViewport(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; }

		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4 GetViewProjection() const { return GetProjection() * m_ViewMatrix; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrollEvent& event);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;

		glm::vec3 CalculatePosition() const;
		glm::quat GetOrientation() const;

		glm::vec3 GetRightDirection() const;
		glm::vec3 GetUpDirection() const;
		glm::vec3 GetForwardDirection() const;
	private:
		float m_FOV = 45.0f;
		float m_AspectRatio = 1.778f;
		float m_NearClip = 0.1f, m_FarClip = 1000.0f;

		float m_Distance = 10.0f;
		float m_Pitch = 0.0f, m_Yaw = 0.0f;
		float m_ViewportWidth = 1280, m_ViewportHeight = 720;

		// TODO: Change to uniform initialization syntax. 
		glm::mat4 m_ViewMatrix = glm::mat4(0.0f);
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_FocalPoint = glm::vec3(0.0f);
		glm::vec2 m_MousePosition = glm::vec2(0.0f);
	};
}