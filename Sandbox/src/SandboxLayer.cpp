#include "SandboxLayer.h"

// Temporary
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

SandboxLayer::SandboxLayer()
	: Layer("Sandbox"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition({ 0.0f, 0.0f, 0.0f })
{
}

void SandboxLayer::OnAttach()
{
	Workbench::FramebufferSpecification spec;
	spec.Width = 1280;
	spec.Height = 720;
	m_Framebuffer = Workbench::Framebuffer::Create(spec);

	m_Scene = std::make_shared<Scene>();
	auto entity = m_Scene->CreateEntity();

	uint32_t indices[3] = { 0, 1 ,2 };
	float vertices[3 * 7] = {
	   -0.5f, -0.5f, 0.0f, 1.0f, 0.8f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.0f, 0.5f,
		0.0f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.5f,
	};

	// Vertex shader responsible for structure.
	// Fragment shader responsible for color to structure.

	m_VertexArray.reset(Workbench::VertexArray::Create());
	m_VertexBuffer.reset(Workbench::VertexBuffer::Create(vertices, sizeof(vertices)));
	m_IndexBuffer.reset(Workbench::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	Workbench::BufferLayout layout = {
		{ Workbench::ShaderDataType::Float3, "a_Position" },
		{ Workbench::ShaderDataType::Float4, "a_Color" }
	};

	// Load GLSL file.
	// Read GLSL file data.
	// Get shader layout (uniform, attributes, etc..)
	// Insert shader layout into BufferLayout
	// Pass GLSL file data directly down to Shader::Create

	m_VertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	m_VertexArray->AddIndexBuffer(m_IndexBuffer);

	m_Shader = Workbench::Shader::Create("assets/shader.glsl");
}

void SandboxLayer::OnDetach()
{
}

void SandboxLayer::OnUpdate(Workbench::Timestep ts)
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

	//m_Framebuffer->Bind();
	Workbench::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0 });
	Workbench::RenderCommand::Clear();
	
	m_Camera.SetCameraPosition(m_CameraPosition);
	m_Camera.SetCameraRotation(m_CameraRotation);

	m_Scene->OnUpdate(ts);

	Workbench::Renderer::BeginScene(m_Camera);
	Workbench::Renderer::Submit(m_Shader, m_VertexArray);
	Workbench::Renderer::EndScene();
	//m_Framebuffer->Unbind();
}

void SandboxLayer::OnImGuiRender(Workbench::Timestep ts)
{
	static bool showDemoWindow = true;
	ImGui::Begin("Metrics", &showDemoWindow);
	ImGui::Text("Last frame time: %f ms (%f)", ts.GetMilliseconds(), 1000.0f / ts.GetMilliseconds());
	ImGui::End();
}

void SandboxLayer::OnEvent(Workbench::Event& event)
{

}