#include "wbpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Workbench
{
	PerspectiveCamera::PerspectiveCamera()
	{
		RecalculateProjection();
	}

	void PerspectiveCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		SetProjectionType(ProjectionType::Orthographic);
		
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;
		
		RecalculateProjection();
	}

	void PerspectiveCamera::SetPerspective(float verticalFov, float nearClip, float farClip)
	{
		SetProjectionType(ProjectionType::Perspective);
		
		m_PerspectiveFov = verticalFov;
		m_PerspectiveNear = nearClip;
		m_PerspectiveFar = farClip;
		
		RecalculateProjection();
	}
	
	void PerspectiveCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		m_AspectRatio = (float)width / (float)height;
		RecalculateProjection();
	}

	void PerspectiveCamera::RecalculateProjection()
	{
		if (GetProjectionType() == ProjectionType::Orthographic)
		{
			float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
			float orthoBottom = -m_OrthographicSize * 0.5f;
			float orthoTop = m_OrthographicSize * 0.5f;

			SetProjection(glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, m_OrthographicNear, m_OrthographicFar));
		}
		else if (GetProjectionType() == ProjectionType::Perspective)
		{
			SetProjection(glm::perspective(m_PerspectiveFov, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar));
		}
	}
}