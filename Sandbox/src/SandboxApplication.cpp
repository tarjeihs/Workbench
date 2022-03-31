#include <Workbench.h>

// Example
class SandboxLayer : public Workbench::Layer
{
public:
	SandboxLayer()
		: Layer("Sandbox")
	{
	}

	void OnUpdate() override
	{

	}

	void OnEvent(Workbench::Event& event) override
	{
		WB_CLIENT_TRACE("{0}", event);
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