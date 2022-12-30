#include "wbpch.h"
#include "Engine/Scene/Entity.h"

namespace Workbench
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}