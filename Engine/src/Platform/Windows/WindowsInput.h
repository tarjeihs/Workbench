#pragma once

#include "Engine/Core/Input.h"

namespace Workbench
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool KeyPressedImpl(int keyCode) override;
		virtual bool MouseButtonPressedImpl(int keyCode) override;

		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual bool JoystickButtonPressedImpl(int keyCode) override;
		virtual bool JoystickHatButtonPressedImpl(int keyCode) override;

		virtual float GetJoystickLeftXImpl() override;
		virtual float GetJoystickLeftYImpl() override;

		virtual float GetJoystickRightXImpl() override;
		virtual float GetJoystickRightYImpl() override;

		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual std::pair<float, float> GetJoystickLeftPositionImpl() override;
		virtual std::pair<float, float> GetJoystickRightPositionImpl() override;
	};
}