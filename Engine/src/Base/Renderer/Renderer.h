#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Workbench
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResize(uint32_t, uint32_t height);

		static void BeginScene(OrthographicCamera& orthographicCamera);
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

		static SceneData* m_SceneData;
	};
}