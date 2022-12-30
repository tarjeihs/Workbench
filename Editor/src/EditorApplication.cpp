#include "Workbench.h"
#include "Engine/Core/Entrypoint.h"

#include "EditorLayer.h"

class EditorApplication : public Workbench::Application
{
public:
	EditorApplication()
		: Application("Editor")
	{
		m_EditorLayer = new EditorLayer();
	}

	~EditorApplication()
	{
		delete m_EditorLayer;
	}
private:
	EditorLayer* m_EditorLayer;
};

Workbench::Application* Workbench::CreateApplication()
{
	return new EditorApplication();
}