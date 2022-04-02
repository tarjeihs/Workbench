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

	}
};

class SandboxApplication : public Workbench::Application
{
public:
	SandboxApplication()
	{
		PushLayer(new SandboxLayer());
		PushOverlay(new Workbench::ImGuiLayer());
	}
	 
	~SandboxApplication()
	{
	}
};

Workbench::Application* Workbench::CreateApplication()
{
	return new SandboxApplication();
}