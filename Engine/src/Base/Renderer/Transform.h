#pragma once

#include <glm/glm.hpp>

namespace Workbench
{
	class Transform
	{
	public:

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Rotation;
		glm::vec3 m_Euler;
	};
}