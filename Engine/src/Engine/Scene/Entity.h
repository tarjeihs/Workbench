#pragma once

#include "Engine/Scene/Scene.h"

#include <entt/entt.hpp>

namespace Workbench
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			WB_ENGINE_ASSERT(!HasComponent<T>(), "Component is attached.");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			WB_ENGINE_ASSERT(HasComponent<T>(), "Component is not attached.");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Scene->m_Registry.try_get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			WB_ENGINE_ASSERT(HasComponent<T>(), "Component is not attached.");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		entt::entity m_EntityHandle { entt::null };
		Scene* m_Scene = nullptr;
	};
}