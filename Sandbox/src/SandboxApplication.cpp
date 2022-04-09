#include <Workbench.h>

// Temporary
#include "glm/gtc/matrix_transform.hpp"

class SandboxLayer : public Workbench::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({ 0.0f, 0.0f, 0.0f })
	{
		uint32_t indices[3] = { 0, 1 ,2 };
		float vertices[3 * 7] = {
		   -0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 0.5f,
			0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f,
		};

		std::shared_ptr<Workbench::VertexBuffer> m_VertexBuffer;
		std::shared_ptr<Workbench::IndexBuffer> m_IndexBuffer;

		m_VertexArray.reset(Workbench::VertexArray::Create());
		m_VertexBuffer.reset(Workbench::VertexBuffer::Create(vertices, sizeof(vertices)));
		m_IndexBuffer.reset(Workbench::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		Workbench::BufferLayout layout = {
			{ Workbench::ShaderDataType::Float3, "a_Position" },
			{ Workbench::ShaderDataType::Float4, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() 
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() 
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Workbench::Shader::Create(vertexSource, fragmentSource));
	}

	virtual void OnUpdate(Workbench::Timestep ts) override
	{
		if (Workbench::Input::KeyPressed(WB_KEY_LEFT))
			m_CameraPosition.x -= m_CameraPositionSpeed * ts;
		else if (Workbench::Input::KeyPressed(WB_KEY_RIGHT)) 
			m_CameraPosition.x += m_CameraPositionSpeed * ts;

		if (Workbench::Input::KeyPressed(WB_KEY_DOWN))
			m_CameraPosition.y -= m_CameraPositionSpeed * ts;
		else if (Workbench::Input::KeyPressed(WB_KEY_UP)) 
			m_CameraPosition.y += m_CameraPositionSpeed * ts;

		if (Workbench::Input::KeyPressed(WB_KEY_A)) 
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		else if (Workbench::Input::KeyPressed(WB_KEY_D)) 
			m_CameraRotation += m_CameraRotationSpeed * ts;


		Workbench::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
		Workbench::RenderCommand::Clear();
		
		m_Camera.SetCameraPosition(m_CameraPosition);
		m_Camera.SetCameraRotation(m_CameraRotation);

		Workbench::Renderer::BeginScene(m_Camera);
		Workbench::Renderer::EndScene();

		Workbench::Renderer::Submit(m_Shader, m_VertexArray);

		Workbench::Renderer::EndScene();
	}

	virtual void OnImGuiRender(Workbench::Timestep ts) override
	{
		
	}

	virtual void OnEvent(Workbench::Event& event) override
	{
	}
private:
	std::shared_ptr<Workbench::Shader> m_Shader;
	std::shared_ptr<Workbench::VertexArray> m_VertexArray;

	Workbench::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraPositionSpeed = 1.0f;
	float m_CameraRotationSpeed = 10.0f;
};

class SandboxApplication : public Workbench::Application
{
public:
	SandboxApplication()
	{
		PushLayer(new SandboxLayer());
	}
	 
	~SandboxApplication()
	{

	}
};

Workbench::Application* Workbench::CreateApplication()
{
	return new SandboxApplication();
}