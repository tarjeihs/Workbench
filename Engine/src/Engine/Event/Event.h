#pragma once

#include "Engine/Core/Base.h"

#include <functional>

namespace Workbench
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		ApplicationTick, ApplicationUpdate, ApplicationRender,
		KeyPressed, KeyReleased, KeyType,
		MouseButtonPressed, MouseButtonReleased, MouseMove, MouseScroll,
		JoystickConnected, JoystickDisconnected,
		JoystickButtonPressed, JoystickButtonReleased, JoystickMoveL, JoystickMoveR
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication			= 1 << 0,
		EventCategoryInput					= 1 << 1,
		EventCategoryKeyboard				= 1 << 2,
		EventCategoryMouse					= 1 << 3,
		EventCategoryMouseButton			= 1 << 4,
		EventCategoryJoystickConnected		= 1 << 5,
		EventCategoryJoystickDisconnected	= 1 << 6,
		EventCategoryJoystickMove			= 1 << 7,
		EventCategoryJoystickButton			= 1 << 8
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
		bool IsHandled = false;
	
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.IsHandled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};


	inline std::ostream& operator<<(std::ostream& os, const Event& event)
	{
		return os << event.ToString();
	}
}