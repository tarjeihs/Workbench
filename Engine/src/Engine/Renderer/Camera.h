#pragma once

#include "Engine/Event/ApplicationEvent.h"

#include <glm/glm.hpp>
#include "Engine/Core/Timestep.h"

namespace Workbench
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection) 
			: m_Projection(projection) {}
		virtual ~Camera() = default;

		inline const glm::mat4& GetProjection() const { return m_Projection; }
	protected:
		glm::mat4 m_Projection = glm::mat4(1.0f);
	};
}