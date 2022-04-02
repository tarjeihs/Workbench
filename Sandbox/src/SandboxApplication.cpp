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
		if (event.GetEventType() == Workbench::EventType::KeyPressed)
		{
			Workbench::KeyPressedEvent& _event = (Workbench::KeyPressedEvent&)event;
			WB_CLIENT_TRACE("{0}", _event.GetKeyCode());
		}
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