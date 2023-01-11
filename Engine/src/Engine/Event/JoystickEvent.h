#pragma once

#include "Engine/Event/Event.h"

namespace Workbench
{
	class JoystickConnectedEvent : public Event
	{
	public:
		JoystickConnectedEvent() {}

		EVENT_CLASS_CATEGORY(EventCategoryJoystickConnected | EventCategoryInput)
		EVENT_CLASS_TYPE(JoystickConnected)
	};

	class JoystickDisconnectedEvent : public Event
	{
	public:
		JoystickDisconnectedEvent() {}
	
		EVENT_CLASS_CATEGORY(EventCategoryJoystickDisconnected | EventCategoryInput);
		EVENT_CLASS_TYPE(JoystickDisconnected);
	};

	class JoystickButtonEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryJoystickButton | EventCategoryInput)
	protected:
		JoystickButtonEvent(int keyCode)
			: m_KeyCode(keyCode) {}

		int m_KeyCode;
	};

	class JoystickButtonPressedEvent : public JoystickButtonEvent
	{
	public:
		JoystickButtonPressedEvent(int keyCode)
			: JoystickButtonEvent(keyCode) {}

		EVENT_CLASS_TYPE(JoystickButtonPressed)
	};

	class JoystickButtonReleasedEvent : public JoystickButtonEvent
	{
	public:
		JoystickButtonReleasedEvent(int keyCode)
			: JoystickButtonEvent(keyCode) {}

		EVENT_CLASS_TYPE(JoystickButtonReleased)
	};

	class JoystickMoveEvent : public Event
	{
	public:
		JoystickMoveEvent(float joystickX, float joystickY) 
			: m_JoystickX(joystickX), m_JoystickY(joystickY) {}

		inline float GetJoystickX() const { return m_JoystickX; }
		inline float GetJoystickY() const { return m_JoystickY; }

		EVENT_CLASS_CATEGORY(EventCategoryJoystickMove | EventCategoryInput)
	private:
		float m_JoystickX;
		float m_JoystickY;
	};

	class JoystickMoveLEvent : public JoystickMoveEvent
	{
	public:
		JoystickMoveLEvent(float joystickX, float joystickY)
			: JoystickMoveEvent(joystickX, joystickY) {}

		EVENT_CLASS_TYPE(JoystickMoveL)
	};

	class JoystickMoveREvent : public JoystickMoveEvent
	{	
	public:
		JoystickMoveREvent(float joystickX, float joystickY)
			: JoystickMoveEvent(joystickX, joystickY)
		{
		}

		EVENT_CLASS_TYPE(JoystickMoveR)
	};
}