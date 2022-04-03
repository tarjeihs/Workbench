#include <Workbench.h>

class SandboxLayer : public Workbench::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox")
	{
	}

	virtual void OnUpdate() override
	{

	}

	virtual void OnImGuiRender() override
	{
		
	}

	virtual void OnEvent(Workbench::Event& event) override
	{
		
	}
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