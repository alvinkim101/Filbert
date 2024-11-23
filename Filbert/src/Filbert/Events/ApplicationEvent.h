#pragma once

#include "Event.h"

namespace Filbert
{
	class FILBERT_API ApplicationTickEvent : public Event
	{
	public:
		EVENT_CLASS_NAME_AND_TYPE(ApplicationTick)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)
	};

	class FILBERT_API ApplicationUpdateEvent : public Event
	{
		EVENT_CLASS_NAME_AND_TYPE(ApplicationUpdate)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)
	};

	class FILBERT_API ApplicationRenderEvent : public Event
	{
		EVENT_CLASS_NAME_AND_TYPE(ApplicationRender)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)
	};

	class FILBERT_API WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_NAME_AND_TYPE(WindowClose)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)
	};

	class FILBERT_API WindowFocusEvent : public Event
	{
	public:
		EVENT_CLASS_NAME_AND_TYPE(WindowFocus)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)
	};

	class FILBERT_API WindowUnfocusEvent : public Event
	{
	public:
		EVENT_CLASS_NAME_AND_TYPE(WindowUnfocus)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)
	};

	class FILBERT_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

		EVENT_CLASS_NAME_AND_TYPE(WindowResize)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)

		std::pair<unsigned int, unsigned int> GetResolution() const { return { m_width, m_height }; }
		unsigned int GetWidth() const { return m_width; }
		unsigned int GetHeight() const { return m_height; }

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "MouseResizedEvent: width = " << m_width << ", height = " << m_height;

			return ss.str();
		}

	private:
		unsigned int m_width = 0, m_height = 0;
	};

	class FILBERT_API WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(float x, float y) : m_x(x), m_y(y) {}

		EVENT_CLASS_NAME_AND_TYPE(WindowMove)
		EVENT_CLASS_CATEGORIES(EventCategoryApplication)

		std::pair<float, float> GetCoordinates() const { return { m_x, m_y }; }
		float GetWidth() const { return m_x; }
		float GetHeight() const { return m_y; }

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "WindowMovedEvent: x coordinate = " << m_x << ", y coordinate = " << m_y;

			return ss.str();
		}

	private:
		float m_x = 0.0f, m_y = 0.0f;
	};
}
