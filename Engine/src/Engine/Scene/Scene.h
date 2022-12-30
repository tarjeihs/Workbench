#pragma once

#include "Engine/Core/Timestep.h"
#include "Engine/Core/UUID.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace Workbench
{
	class Entity;
	
	class Scene
	{
	public:
		Scene();
		~Scene();

		void OnEnable();
		void OnDisable();
		void OnUpdate(Timestep ts);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());

		void DestroyEntity(Entity& entity);
		void DestroyEntity(const UUID& uuid);

		Entity FindEntityByName(std::string_view name);
		Entity FindEntityByUUID(UUID uuid);
	private:
		entt::registry m_Registry;

		std::unordered_map<UUID, entt::entity> m_EntityMap;

		uint32_t m_EntityCount;

		friend class Entity;
	};
}