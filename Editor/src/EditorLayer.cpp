#include "EditorLayer.h"

// Temporary
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>

EditorLayer::EditorLayer()
	: Layer("Editor")
{
}

void EditorLayer::OnAttach()
{

}

void EditorLayer::OnDetach()
{

}

void EditorLayer::OnUpdate(Workbench::Timestep ts)
{

}

void EditorLayer::OnImGuiRender(Workbench::Timestep ts)
{
	static bool showDemoWindow = true;
	ImGui::Begin("Metrics", &showDemoWindow);
	ImGui::Text("Last frame time: %f ms (%f)", ts.GetMilliseconds(), 1000.0f / ts.GetMilliseconds());
	ImGui::End();
}

void EditorLayer::OnEvent(Workbench::Event& event)
{

}