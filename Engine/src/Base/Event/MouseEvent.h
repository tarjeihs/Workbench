#pragma once

#include "Event.h"

namespace Workbench
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		float GetMouseX() const { return m_MouseX; }
		float GetMouseY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseMove)
	private:
		float m_MouseX;
		float m_MouseY;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(const float xScrollOffset, const float yScrollOffset) 
			: m_ScrollXOffset(xScrollOffset), m_ScrollYOffset(yScrollOffset) {}

		float GetScrollXOffset() const { return m_ScrollXOffset; }
		float GetScrollYOffset() const { return m_ScrollYOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << m_ScrollXOffset << ", " << m_ScrollYOffset;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseScroll)
	private:
		float m_ScrollXOffset;
		float m_ScrollYOffset;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(const int keyCode, const int repeatCount)
			: m_KeyCode(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		// Purely for debugging purposes
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseButtonPressed)
	private:
		int m_KeyCode;
		int m_RepeatCount;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(const int keyCode)
			: m_KeyCode(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
		EVENT_CLASS_TYPE(MouseButtonReleased)
	private:
		int m_KeyCode;
	};
}