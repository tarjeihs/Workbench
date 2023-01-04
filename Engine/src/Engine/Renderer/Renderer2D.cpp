#include "wbpch.h"
#include "Engine/Renderer/Renderer2D.h"

#include "Engine/Renderer/RenderCommand.h"
#include "Engine/Renderer/UniformBuffer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Workbench
{
	struct Renderer2DData
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		//std::shared_ptr<Shader> FlatColorShader;

		
		struct CameraBuffer
		{
			glm::mat4 ViewProjection;
		};
		CameraBuffer CameraBuffer;
		std::shared_ptr<UniformBuffer> CameraUniformBuffer;

		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		std::shared_ptr<Shader> TextureShader;
		//std::shared_ptr<Texture2D> WhiteTexture;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f,  0.5f, 0.0f, -0.5f,  0.5f, 0.0f };
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		
		squareVB->SetLayout({ { ShaderDataType::Float3, "a_Position" } });
		
		s_Data.QuadVertexArray->AddVertexBuffer(squareVB);
		s_Data.QuadVertexArray->AddIndexBuffer(squareIB);

		//s_Data.FlatColorShader = Shader::Create("assets/FlatColor.glsl");
		s_Data.CameraUniformBuffer = UniformBuffer::Create(sizeof(Renderer2DData::CameraBuffer), 0);
	}

	void Renderer2D::Shutdown()
	{

	}

	void Renderer2D::BeginScene(const EditorCamera& camera)
	{
		glm::mat4 viewProj = camera.GetViewProjection();

		s_Data.CameraBuffer.ViewProjection = camera.GetViewProjection();
		s_Data.CameraUniformBuffer->SetData(&s_Data.CameraBuffer, sizeof(Renderer2DData::CameraBuffer));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		//std::dynamic_pointer_cast<OpenGLShader>(s_Data.FlatColorShader)->Bind();
		//std::dynamic_pointer_cast<OpenGLShader>(s_Data.FlatColorShader)->SetFloat3("u_Position", position);
		//std::dynamic_pointer_cast<OpenGLShader>(s_Data.FlatColorShader)->SetFloat3("u_Size", position);
		//std::dynamic_pointer_cast<OpenGLShader>(s_Data.FlatColorShader)->SetFloat4("u_Color", color);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}
}