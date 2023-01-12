#include "wbpch.h"
#include "Platform/Windows/WindowsInput.h"

#include "Engine/Core/Application.h"

#include <GLFW/glfw3.h>

// Cleanup!
namespace Workbench
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::KeyPressedImpl(int keyCode)
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

	bool WindowsInput::JoystickButtonPressedImpl(int keyCode)
	{
		int count = 0;
		const unsigned char* state = glfwGetJoystickButtons(WB_JOYSTICK_DEVICE_1, &count);
		return state[keyCode] == GLFW_PRESS;
	}

	bool WindowsInput::JoystickHatButtonPressedImpl(int keyCode)
	{
		int count = 0;
		const unsigned char* state = glfwGetJoystickHats(WB_JOYSTICK_DEVICE_1, &count);
		return state[keyCode] == GLFW_HAT_UP;

		return false;
	}

	float WindowsInput::GetJoystickLeftXImpl()
	{
		auto [joystickX, joystickY] = GetJoystickLeftPositionImpl();
		return std::abs(joystickX) >= JOYSTICK_DEADZONE_THRESHOLD ? joystickX : 0.0f;
	}

	float WindowsInput::GetJoystickLeftYImpl()
	{
		auto [joystickX, joystickY] = GetJoystickLeftPositionImpl();
		return std::abs(joystickY) >= JOYSTICK_DEADZONE_THRESHOLD ? joystickY : 0.0f;
	}

	float WindowsInput::GetJoystickRightXImpl()
	{
		auto [joystickX, joystickY] = GetJoystickRightPositionImpl();
		return std::abs(joystickX) >= JOYSTICK_DEADZONE_THRESHOLD ? joystickX : 0.0f;
	}

	float WindowsInput::GetJoystickRightYImpl()
	{
		auto [joystickX, joystickY] = GetJoystickRightPositionImpl();
		return std::abs(joystickY) >= JOYSTICK_DEADZONE_THRESHOLD ? joystickY : 0.0f;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double mouseX, mouseY;
		glfwGetCursorPos(window, &mouseX, &mouseY);

		return { (float)mouseX, (float)mouseY };
	}

	// Only supporting one controller at the moment.
	std::pair<float, float> WindowsInput::GetJoystickLeftPositionImpl()
	{
		WB_ENGINE_ASSERT(glfwJoystickPresent(WB_JOYSTICK_DEVICE_1), "Attempting to call function with data pointing to null.");
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int count = 0; 
		const float* state = glfwGetJoystickAxes(WB_JOYSTICK_DEVICE_1, &count);
		
		return { state[0], state[1] };
	}

	// Only supporting one controller at the moment.
	std::pair<float, float> WindowsInput::GetJoystickRightPositionImpl()
	{
		WB_ENGINE_ASSERT(glfwJoystickPresent(WB_JOYSTICK_DEVICE_1), "Attempting to call function with data pointing to null.");
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int count = 0;
		const float* state = glfwGetJoystickAxes(WB_JOYSTICK_DEVICE_1, &count);

		return { state[2], state[3] };
	}
}

