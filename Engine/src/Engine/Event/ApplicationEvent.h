#pragma once

#include "Engine/Event/Event.h"

namespace Workbench
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ApplicationTickEvent : public Event
	{
	public:
		ApplicationTickEvent() = default;

		EVENT_CLASS_TYPE(ApplicationTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ApplicationUpdateEvent : public Event
	{
	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_TYPE(ApplicationUpdate);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ApplicationRenderEvent : public Event
	{
	public:
		ApplicationRenderEvent() = default;

		EVENT_CLASS_TYPE(ApplicationRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}