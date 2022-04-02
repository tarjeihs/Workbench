#include "wbpch.h"
#include "WindowsInput.h"

#include "Base/Application.h"

#include <GLFW/glfw3.h>

namespace Workbench
{
	Input* Input::s_Instance = new WindowsInput();

	bool Workbench::WindowsInput::KeyPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::MouseButtonPressedImpl(int keyCode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, keyCode);

		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[mouseX, mouseY] = GetMousePositionImpl();
		return mouseX;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[mouseX, mouseY] = GetMousePositionImpl();
		return mouseY;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		return { (float)mouseX, (float)mouseY };
	}
}

