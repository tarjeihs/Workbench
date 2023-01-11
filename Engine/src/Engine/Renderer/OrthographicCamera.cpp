#include "wbpch.h"
#include "Engine/Renderer/OrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Workbench
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float zNear, float zFar)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;	
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		// Should try not do every recalculations all the time to increase performance.
 		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_CameraPosition) * 
 			glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0.0f, 0.0f, 1.0f));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}