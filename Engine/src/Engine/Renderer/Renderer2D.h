#pragma once

#include "Engine/Renderer/ProjectionCamera.h"
#include "Engine/Renderer/EditorCamera.h"

#include "Engine/Scene/Entity.h"

namespace Workbench
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();
		
		static void BeginScene(const ProjectionData& projectionData);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const ProjectionCamera& camera, const glm::mat4& transform);
		static void EndScene();

		static void DrawQuad(const glm::vec2& position, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec4& color);
		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	private:
		//static void Flush();
		//static void Reset();
	};
}