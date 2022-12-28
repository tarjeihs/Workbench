#include "wbpch.h"
#include "Engine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Workbench
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& orthographicCamera)
	{
		m_SceneData->ViewProjectionMatrix = orthographicCamera.GetProjectionViewMatrix();
	}

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform)
	{
		shader->Bind();
		vertexArray->Bind();
		
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

		
		RenderCommand::DrawIndexed(vertexArray);
	}
}