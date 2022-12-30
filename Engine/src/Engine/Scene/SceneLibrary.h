#pragma once

#include "Engine/Scene/Scene.h"

#include <unordered_map>

// WIP

namespace Workbench
{
	// Only one runtime Scene currently supported.
	// Make possibility to serialize and deserialize .scene files.
	class SceneLibrary
	{
	public:
		//void AddScene(const std::string& name, Scene* scene = new Scene());
		//void RemoveScene(const std::string& name);

		inline void OnEnable() { s_Scene->OnEnable(); }
		inline void OnUpdate(Timestep ts) { s_Scene->OnUpdate(ts); }
		inline void OnDisable() { s_Scene->OnDisable(); }

		static inline Scene& GetScene() { return *s_Scene; }
	private:
		static Scene* s_Scene;

		//Scene& m_ActiveScene;
		//std::unordered_map<const std::string, Scene*> m_Scenes;
	};
}