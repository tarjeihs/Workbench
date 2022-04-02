#pragma once

#include "Base/Input.h"

namespace Workbench
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool KeyPressedImpl(int keyCode) override;
		virtual bool MouseButtonPressedImpl(int keyCode) override;

		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;

		virtual std::pair<float, float> GetMousePositionImpl() override;
	};
}