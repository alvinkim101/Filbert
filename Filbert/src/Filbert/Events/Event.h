#pragma once

#include "Filbert/Core.h"

namespace Filbert
{
	enum class EventType
	{
		None,
		WindowClose, WindowFocus, WindowUnfocus, WindowResize, WindowMove,
		ApplicationTick, ApplicationUpdate, ApplicationRender,
		KeyPress, KeyRelease,
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};

	enum EventCategory
	{
		EventCategoryNone			= 0,
		EventCategoryApplication	= 0b1,
		EventCategoryInput			= 0b10,
		EventCategoryKeyboard		= 0b100,
		EventCategoryMouse			= 0b1000,
		EventCategoryMouseButton	= 0b10000
	};

#define EVENT_CLASS_NAME_AND_TYPE(event) const char* GetName() const override { return #event; } \
										 constexpr EventType GetType() const override { return GetTypeStatic(); } \
										 static constexpr EventType GetTypeStatic() { return EventType::event; }
									   

#define EVENT_CLASS_CATEGORIES(categories) constexpr int GetCategories() const override { return GetCategoriesStatic(); } \
										   static constexpr int GetCategoriesStatic() { return categories; }

	class Event
	{
	public:
		virtual const char* GetName() const = 0;
		virtual constexpr EventType GetType() const = 0;
		virtual constexpr int GetCategories() const = 0;

		virtual std::string Info() const { return GetName(); };

		bool CointainsCategory(EventCategory category) const
		{
			return GetCategories() & category;
		}

		bool handled = false;
	};

	class EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_event(event) {}

		template <typename T>
		bool Dispatch(EventFn<T> f)
		{
			if (m_event.GetType() == T::GetTypeStatic())
			{
				m_event.handled = f(dynamic_cast<T&>(m_event));
				return true;
			}

			return false;
		}

	private:
		Event& m_event;
	};
}
