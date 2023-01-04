#include "Workbench.h"
#include "Engine/Core/Entrypoint.h"

#include "EditorLayer.h"

namespace Workbench
{
	class EditorApplication : public Application
	{
	public:
		EditorApplication()
			: Application("Workbench Editor", 1280, 720)
		{
			PushLayer(new EditorLayer());
		}

		~EditorApplication()
		{
		}
	private:
	};

	Application* CreateApplication()
	{
		return new EditorApplication();
	}
}