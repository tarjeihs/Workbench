#pragma once

#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/ProjectionCamera.h"

namespace Workbench
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t, uint32_t height);

		static void BeginScene(ProjectionCamera& projectionCamera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, 
			const std::shared_ptr<VertexArray>& vertexArray, 
			const glm::mat4 transform = glm::mat4(1.0f));

		static RendererAPI::APIType GetAPI() { return RendererAPI::GetAPIType(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static std::unique_ptr<SceneData> m_SceneData;
	};
}