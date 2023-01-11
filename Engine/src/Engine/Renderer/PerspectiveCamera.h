#pragma once

#include "Engine/Renderer/ProjectionCamera.h"

#include <glm/glm.hpp>

namespace Workbench
{
	class PerspectiveCamera : public ProjectionCamera
	{
	public:
		PerspectiveCamera();
		virtual ~PerspectiveCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetPerspective(float verticalFOV, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		inline float GetOrthographicSize() const { return m_OrthographicSize; }
		inline void GetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }
		inline float GetOrthographicNearClip() const { return m_OrthographicSize; }
		inline void GetOrthographicNearClip(float nearClip) { m_OrthographicSize = nearClip; RecalculateProjection(); }
		inline float GetOrthographicFarClip() const { return m_OrthographicSize; }
		inline void GetOrthographicFarClip(float farClip) { m_OrthographicSize = farClip; RecalculateProjection(); }

		inline float GetPerspectiveVerticalFov() const { return m_PerspectiveFov; }
		inline void SetPerspectiveVerticalFov(float fov) { m_PerspectiveFov = fov; RecalculateProjection(); }
		inline float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
		inline void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculateProjection(); }
		inline float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
		inline void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculateProjection(); }
	private:
		void RecalculateProjection();
	private:
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_PerspectiveFov = glm::radians(45.0f);
		float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

		// 1280 * 720
		float m_AspectRatio = 1.7777778f;
	};
}