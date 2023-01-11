#pragma once

#include "Engine/Scene/Scene.h"
#include "Engine/Renderer/ProjectionCamera.h"

#include <entt/entt.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Workbench
{
	struct UUIDComponent
	{
		UUID Id;

		UUIDComponent() = default;
		UUIDComponent(const UUIDComponent& other) = default;
		UUIDComponent(const UUID& uuid)
			: Id(uuid)
		{
		}
	};

	struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent& other) = default;
		TagComponent(const std::string& tag = "Entity")
			: Tag(tag)
		{
		}
	};

	struct TransformComponent
	{
		glm::vec3 Translation = glm::vec3(0.0f);
		glm::vec3 Rotation = glm::vec3(0.0f);
		glm::vec3 Scale = glm::vec3(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& color)
			: Color(color)
		{
		}
	};
	
	struct CameraComponent
	{
		ProjectionCamera Camera;
		bool Primary = true;
		bool FixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = default;
		CameraComponent(const ProjectionCamera& camera)
			: Camera(camera)
		{
		}

		template<typename T, typename ... Args>
		void Bind(Args&& ... args)
		{
			Camera = T(std::forward<Args>(args)...);
		}
	};
	
	class ScriptableEntity;

	struct NativeScriptComponent
	{
		ScriptableEntity* Script = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Script; nsc->Script = nullptr; };
		}
	};

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		inline T& AddComponent(Args&&... args) const
		{
			WB_ENGINE_ASSERT(!HasComponent<T>(), "Component is attached.");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		inline T& GetComponent() const
		{
			WB_ENGINE_ASSERT(HasComponent<T>(), "Component is not attached.");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}
		
		template<typename T>
		inline void RemoveComponent() const
		{
			WB_ENGINE_ASSERT(HasComponent<T>(), "Component is not attached.");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		inline bool HasComponent() const
		{
			return m_Scene->m_Registry.try_get<T>(m_EntityHandle);
		}

		inline UUID GetUUID() { return GetComponent<UUIDComponent>().Id; }
		inline const std::string& GetName() { return GetComponent<TagComponent>().Tag; }

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
	private:
		entt::entity m_EntityHandle { entt::null };
		Scene* m_Scene = nullptr;
	};
}