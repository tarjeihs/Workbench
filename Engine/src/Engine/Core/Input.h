#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Core/KeyCode.h"

#include <map>

namespace Workbench
{
	constexpr float JOYSTICK_DEADZONE_THRESHOLD = 0.15f;

	class Input
	{
	public:
		inline static bool KeyPressed(int keyCode) { return s_Instance->KeyPressedImpl(keyCode); }
		inline static bool MouseButtonPressed(int keyCode) { return s_Instance->MouseButtonPressedImpl(keyCode); }

		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		inline static bool JoystickButtonPressed(int keyCode) { return s_Instance->JoystickButtonPressedImpl(keyCode); }
		inline static bool JoystickHatButtonPressed(int keyCode) { return s_Instance->JoystickHatButtonPressedImpl(keyCode); }

		inline static float GetJoystickLeftX() { return s_Instance->GetJoystickLeftXImpl(); };
		inline static float GetJoystickLeftY() { return s_Instance->GetJoystickLeftYImpl(); };

		inline static float GetJoystickRightX() { return s_Instance->GetJoystickRightXImpl(); };
		inline static float GetJoystickRightY() { return s_Instance->GetJoystickRightYImpl(); };

		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static std::pair<float, float> GetJoystickLeftPosition() { return s_Instance->GetJoystickLeftPositionImpl(); }
		inline static std::pair<float, float> GetJoystickRightPosition() { return s_Instance->GetJoystickRightPositionImpl(); }
	protected:
		// Pure virtual implementation of global functions above.
		virtual bool KeyPressedImpl(int keyCode) = 0;
		virtual bool MouseButtonPressedImpl(int keyCode) = 0;

		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

		virtual bool JoystickButtonPressedImpl(int keyCode) = 0;
		virtual bool JoystickHatButtonPressedImpl(int keyCode) = 0;
		
		virtual float GetJoystickLeftXImpl() = 0;
		virtual float GetJoystickLeftYImpl() = 0;

		virtual float GetJoystickRightXImpl() = 0;
		virtual float GetJoystickRightYImpl() = 0;

		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual std::pair<float, float> GetJoystickLeftPositionImpl() = 0;
		virtual std::pair<float, float> GetJoystickRightPositionImpl() = 0;
	private:
		static Input* s_Instance;
	};
}