#include "wbpch.h"
#include "Engine/Scene/Scene.h"

#include "Engine/Scene/Entity.h"
#include "Engine/Scene/ScriptableEntity.h"
#include "Engine/Scene/Object.h"

namespace Workbench
{
	Scene::Scene()
	{
		m_Registry = entt::registry { };
	}

	Scene::~Scene()
	{
		m_Registry.clear();
	}

	void Scene::OnEnable()
	{
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			if (nsc.Script == nullptr)
			{
				nsc.Script = nsc.InstantiateScript();
				nsc.Script->m_Entity = Entity{ entity, this };
				nsc.Script->OnCreate();
			}
		});
	}

	void Scene::OnDisable()
	{
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			if (nsc.Script != nullptr)
			{
				nsc.Script->OnDestroy();
				nsc.DestroyScript(&nsc);
			}
		});
	}

	void Scene::OnUpdate(Timestep ts)
	{
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			nsc.Script->OnUpdate(ts);
		});
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		return CreateEntityWithUUID(UUID(), name);
	}

	Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TagComponent>(name);
		entity.AddComponent<UUIDComponent>(uuid);
		entity.AddComponent<TransformComponent>();
		
		m_EntityMap[uuid] = entity;

		m_EntityCount++;
		
		return entity;
	}

	void Scene::DestroyEntity(Entity& entity)
	{
		DestroyEntity(entity.GetUUID());
	}

	void Scene::DestroyEntity(const UUID& uuid)
	{
		m_Registry.destroy(m_EntityMap[uuid]);
		m_EntityMap.erase(uuid);

		m_EntityCount--;
	}

	Entity Scene::FindEntityByName(std::string_view name)
	{
		auto view = m_Registry.view<TagComponent>();

		for (auto entity : view)
		{
			const TagComponent& tc = view.get<TagComponent>(entity);
			if (tc.Tag == name)
				return Entity { entity, this };
		}

		return {};
	}

	Entity Scene::FindEntityByUUID(UUID uuid)
	{
		if (m_EntityMap.find(uuid) != m_EntityMap.end())
			return { m_EntityMap.at(uuid), this };

		return {};
	}
}