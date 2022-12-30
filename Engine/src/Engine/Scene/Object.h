#pragma once

// Wrapper for high level ECS and EnTT.

#include "Engine/Scene/Entity.h"

namespace Workbench
{
	class Object
	{
	public:
		Object();
		virtual ~Object() {}
	private:
		Entity m_Entity;
	};
}