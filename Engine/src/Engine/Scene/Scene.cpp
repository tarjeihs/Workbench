#include "wbpch.h"
#include "Engine/Scene/Scene.h"

#include "Engine/Scene/Entity.h"
#include "Engine/Scene/ScriptableEntity.h"
#include "Engine/Scene/Object.h"

#include "Engine/Renderer/Renderer2D.h"

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

	void Scene::OnUpdateRuntime(Timestep ts)
	{
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			nsc.Script->OnUpdate(ts);
		});
	}

	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);
		Renderer2D::DrawQuad({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f }, { 0.5, 0.3, 0.4, 1.0f });
		Renderer2D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		
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