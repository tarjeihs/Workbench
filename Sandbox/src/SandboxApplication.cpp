#include <Workbench.h>
#include <Engine/Core/Entrypoint.h>

#include "SandboxLayer.h"

class SandboxApplication : public Workbench::Application
{
public:
	SandboxApplication()
		: Application("Sandbox")
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