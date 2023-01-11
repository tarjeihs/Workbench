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

		template<typename T>
		T& GetComponent() const
		{
			return m_Entity.GetComponent<T>();
		}
	private:
		Entity m_Entity;
		
		friend class Scene;
	};
}