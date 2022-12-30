#pragma once

#include "Engine/Scene/Scene.h"

#include <entt/entt.hpp>

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
		glm::mat4 Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform)
		{
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
		void RemoveComponent()
		{
			WB_ENGINE_ASSERT(HasComponent<T>(), "Component is not attached.");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
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