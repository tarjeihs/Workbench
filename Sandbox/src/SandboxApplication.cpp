#include <Workbench.h>

class SandboxApplication : public Workbench::Application
{
public:
	SandboxApplication()
	{
	}

	~SandboxApplication()
	{
	}
};

Workbench::Application* Workbench::CreateApplication()
{
	return new SandboxApplication();
}