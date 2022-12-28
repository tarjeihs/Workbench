#include <Workbench.h>
#include <Engine/Core/Entrypoint.h>

#include "SandboxLayer.h"

// https://github.com/TheCherno/Hazel

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