#pragma once

#include "Engine/Scene/Entity.h"

namespace Workbench
{
	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
	private:
		Entity m_Entity;
		
		friend class Scene;
	};
}