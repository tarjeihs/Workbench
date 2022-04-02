#pragma once

#include "Event.h"

namespace Workbench
{
	class MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseKeyCode() const { return m_MouseKeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int mouseKeyCode)
			: m_MouseKeyCode(mouseKeyCode)
		{
		}

		int m_MouseKeyCode;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int mouseKeyCode)
			: MouseButtonEvent(mouseKeyCode)
		{
		}

		// Purely for debugging purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_MouseKeyCode;
			return ss.str();
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

		// Purely for debugging purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_MouseKeyCode;
			return ss.str();
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

		// Purely for debugging purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

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

		// Purely for debugging purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: (" << m_ScrollXOffset << ", " << m_ScrollYOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_ScrollXOffset;
		float m_ScrollYOffset;
	};
} 