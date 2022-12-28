#pragma once

#include <Workbench.h>

class SandboxLayer : public Workbench::Layer
{
public:
	SandboxLayer();
	virtual ~SandboxLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Workbench::Timestep ts) override;
	virtual void OnImGuiRender(Workbench::Timestep ts) override;
	virtual void OnEvent(Workbench::Event& event) override;
private:
	Workbench::ShaderLibrary m_ShaderLibrary;
	
	std::shared_ptr<Workbench::Shader> m_Shader;

	std::shared_ptr<Workbench::VertexArray> m_VertexArray;
	std::shared_ptr<Workbench::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Workbench::IndexBuffer> m_IndexBuffer;

	Workbench::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;

	float m_CameraPositionSpeed = 1.5f;
	float m_CameraRotationSpeed = 30.0f;
};