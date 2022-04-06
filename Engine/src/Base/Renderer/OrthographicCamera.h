#pragma once

#include <glm/glm.hpp>

namespace Workbench
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top, float zNear = -1.0f, float zFar = 1.0f);

		inline void SetCameraPosition(const glm::vec3& position) { m_CameraPosition = position; RecalculateViewMatrix(); }
		inline void SetCameraRotation(const float rotation) { m_CameraRotation = rotation; RecalculateViewMatrix(); }

		inline const glm::vec3& GetPosition() const { return m_CameraPosition; }
		inline const float& GetRotation() const { return m_CameraRotation; }

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetProjectionViewMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		glm::vec3 _m_CameraRotation = { 0.0f, 0.0f, 1.0f };
		float m_CameraRotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}