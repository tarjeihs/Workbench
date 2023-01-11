#pragma once

#include "Engine/Core/Timestep.h"
#include "Engine/Core/UUID.h"

#include "Engine/Renderer/EditorCamera.h"

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <Engine/Renderer/PerspectiveCamera.h>

namespace Workbench
{
	class Entity;

	struct ProjectionData
	{
		ProjectionCamera Camera;
		glm::mat4 Transform;
	};

	class Scene
	{
	public:
		Scene();
		~Scene();
		
		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());

		void DestroyEntity(Entity& entity);
		void DestroyEntity(const UUID& uuid);

		Entity FindEntityByName(std::string_view name);
		Entity FindEntityByUUID(UUID uuid);
		
		void OnViewportResize(uint32_t width, uint32_t height);
	public:
		void UpdateNativeScriptComponent(Timestep ts);
		void UpdateCameraComponent(glm::mat4* cameraTransform, ProjectionCamera* mainCamera);

		void DrawQuad(const ProjectionData& projectionData);

		void DrawQuad(const EditorCamera& camera);
		void DrawQuad(glm::mat4* cameraTransform, ProjectionCamera* mainCamera);
	public:
		// static void UpdateNativeScriptComponent(Timestep ts);
		// static void UpdateCameraComponent(glm::mat4* cameraTransform, ProjectionCamera* mainCamera);
		// static void DrawQuad(const ProjectionData& projectionData);
		// static void DrawQuad(const EditorCamera& camera);
		// static void DrawQuad(glm::mat4* cameraTransform, ProjectionCamera* mainCamera);
	private:
		entt::registry m_Registry;
		std::unordered_map<UUID, entt::entity> m_EntityMap;

		//static Scene* m_ActiveScene;

		friend class Entity;
	};
}