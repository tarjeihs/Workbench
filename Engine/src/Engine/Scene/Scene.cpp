#include "wbpch.h"
#include "Engine/Scene/Scene.h"

#include "Engine/Scene/ScriptableEntity.h"

#include "Engine/Renderer/Renderer2D.h"
#include "Engine/Renderer/ProjectionCamera.h"

// TODO: Generic component updating, allowing custom components to be updated. Also find a universal way through templates. 
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

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (cameraComponent.FixedAspectRatio == true)
				cameraComponent.Camera.SetViewportSize(width, height);
		}
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
				return Entity{ entity, this };
		}

		return {};
	}

	Entity Scene::FindEntityByUUID(UUID uuid)
	{
		if (m_EntityMap.find(uuid) != m_EntityMap.end())
			return { m_EntityMap.at(uuid), this };

		return {};
	}

	// Checking for instance on each update. Should be done in Scene::OnEnable. 
	// TODO: Also not deleting instance, causing memory leaks when scene is destroyed. Delete on Scene::OnDisable
	void Scene::UpdateNativeScriptComponent(Timestep ts)
	{
		m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
		{
			if (nsc.Script == nullptr)
			{
				nsc.Script = nsc.InstantiateScript();
				nsc.Script->m_Entity = Entity { entity, this };
				nsc.Script->OnCreate();
			}
			nsc.Script->OnUpdate(ts);
		});
	}

	// TODO: Stack allocate
	void Scene::UpdateCameraComponent(glm::mat4* cameraTransform, ProjectionCamera* mainCamera)
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			if (camera.Primary)
			{
				cameraTransform = &transform.GetTransform();
				mainCamera = &camera.Camera;
				break;
			}
		}
	}

	void Scene::DrawQuad(const EditorCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
		
			Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
		}

		Renderer2D::EndScene();
	}

	void Scene::DrawQuad(glm::mat4* cameraTransform, ProjectionCamera* mainCamera)
	{
		Renderer2D::BeginScene(*mainCamera, *cameraTransform);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
		}

		Renderer2D::EndScene();
	}
}