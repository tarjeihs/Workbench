#include "wbpch.h"
#include "Engine/Scene/Scene.h"

#include "Engine/Scene/Entity.h"

namespace Workbench
{
	Scene::Scene()
	{
		m_Registry = entt::registry {};	
	}

	Scene::~Scene()
	{
		m_Registry.clear();
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{

	}
}