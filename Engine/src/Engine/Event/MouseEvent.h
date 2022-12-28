#pragma once

#include "Engine/Event/Event.h"

namespace Workbench
{
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int keyCode)
			: m_KeyCode(keyCode)
		{
		}

		int m_KeyCode;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseKeyCode)
			: MouseButtonEvent(mouseKeyCode)
		{
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int mouseKeyCode)
			: MouseButtonEvent(mouseKeyCode)
		{
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float mouseX, float mouseY)
			: m_MouseX(mouseX), m_MouseY(mouseY) {}

		inline float GetMouseX() const { return m_MouseX; }
		inline float GetMouseY() const { return m_MouseY; }

		EVENT_CLASS_TYPE(MouseMove)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float xScrollOffset, float yScrollOffset) 
			: m_ScrollXOffset(xScrollOffset), m_ScrollYOffset(yScrollOffset) {}

		inline float GetScrollXOffset() const { return m_ScrollXOffset; }
		inline float GetScrollYOffset() const { return m_ScrollYOffset; }

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_ScrollXOffset;
		float m_ScrollYOffset;
	};
} 