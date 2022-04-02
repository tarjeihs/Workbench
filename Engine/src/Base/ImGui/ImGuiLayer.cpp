#include "wbpch.h"

#include "ImGuiLayer.h"
#include "Base/Application.h"

#include "Platform/OpenGL/imgui_impl_opengl3.h"

// Temporary for testing
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Workbench
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer") 
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    static bool show = true;

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();

		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
		dispatcher.Dispatch<WindowCloseEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnWindowCloseEvent));

		dispatcher.Dispatch<KeyPressedEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypeEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnKeyTypeEvent));

        dispatcher.Dispatch<MouseMoveEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonMoveEvent));
        dispatcher.Dispatch<MouseScrollEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonScrollEvent));
        dispatcher.Dispatch<MouseButtonPressedEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(WB_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, event.GetWidth(), event.GetHeight());

        return false;
    }

    bool ImGuiLayer::OnWindowCloseEvent(WindowCloseEvent& event)
    {
        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
    {
		ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& event)
    {
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypeEvent(KeyTypeEvent& event)
    {
		ImGuiIO& io = ImGui::GetIO();
        int keyCode = event.GetKeyCode();
        if (keyCode > 0 && keyCode < 0x10000) { io.AddInputCharacter((unsigned short)keyCode); }

        return false;
    }

    bool ImGuiLayer::OnMouseButtonMoveEvent(MouseMoveEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(event.GetMouseX(), event.GetMouseY());

        return false;
    }
    bool ImGuiLayer::OnMouseButtonScrollEvent(MouseScrollEvent& event)
    {
		ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += event.GetScrollXOffset();
        io.MouseWheel += event.GetScrollYOffset();

        return false;
    }
    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
    {
		ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseKeyCode()] = true;

        return false;
    }
    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetMouseKeyCode()] = false;

        return false;
    }
}