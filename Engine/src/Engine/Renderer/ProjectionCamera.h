#pragma once

#include "Engine/Core/Timestep.h"
#include "Engine/Event/ApplicationEvent.h"

#include <glm/glm.hpp>

namespace Workbench
{
	
	class ProjectionCamera
	{
	public:
		enum class ProjectionType { Orthographic = 0, Perspective = 1 }; // 0 = 2D, 1 = 3D

		ProjectionCamera() = default;
		ProjectionCamera(const glm::mat4& projection, ProjectionType projectionType) 
			: m_Projection(projection), m_ProjectionType(projectionType) { }
		virtual ~ProjectionCamera() = default;

		inline const glm::mat4& GetProjection() const { return m_Projection; }
		inline void SetProjection(const glm::mat4& projection) { m_Projection = projection; }

		inline ProjectionType GetProjectionType() const { return m_ProjectionType; }
		inline void SetProjectionType(ProjectionType projectionType) { m_ProjectionType = projectionType; }

		inline const std::pair<uint32_t, uint32_t> GetViewportSize() const { return { m_ViewportWidth, m_ViewportHeight }; }
		inline void SetViewportSize(uint32_t width, uint32_t height) { m_ViewportWidth = width; m_ViewportHeight = height; }
	private:
		glm::mat4 m_Projection = glm::mat4(1.0f);
		
		ProjectionType m_ProjectionType = ProjectionType::Perspective;
		
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	};
}