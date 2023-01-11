#pragma once

#include "Engine/Renderer/ProjectionCamera.h"

#include <glm/glm.hpp>

namespace Workbench
{
	// TODO: Add Camera implementation
	class OrthographicCamera : public ProjectionCamera
	{
	public:
		OrthographicCamera() = default;
		OrthographicCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		void SetProjection(float left, float right, float bottom, float top);

		inline void SetCameraPosition(const glm::vec3& position) { m_CameraPosition = position; RecalculateViewMatrix(); }
		inline void SetCameraRotation(const float rotation) { m_CameraRotation = rotation; RecalculateViewMatrix(); }

		inline const glm::vec3& GetPosition() const { return m_CameraPosition; }
		inline const float& GetRotation() const { return m_CameraRotation; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewProjectionMatrix;
		glm::mat4 m_ViewMatrix;
	};
}