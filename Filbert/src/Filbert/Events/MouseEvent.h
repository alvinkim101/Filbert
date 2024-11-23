#pragma once

#include "Event.h"

namespace Filbert
{
	class FILBERT_API MouseButtonEvent : public Event
	{
	public:
		int GetMouseButtonCode() const { return m_mouseButtonCode; }

		EVENT_CLASS_CATEGORIES(EventCategoryInput | EventCategoryMouse | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(int mouseButtonCode) : m_mouseButtonCode(mouseButtonCode) {}

		int m_mouseButtonCode = 0;
	};

	class FILBERT_API MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int mouseButtonCode) : MouseButtonEvent(mouseButtonCode) {}

		EVENT_CLASS_NAME_AND_TYPE(MouseButtonPress)

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "MouseButtonPressedEvent: mouse button code = " << m_mouseButtonCode;

			return ss.str();
		}
	};

	class FILBERT_API MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int mouseButtonCode) : MouseButtonEvent(mouseButtonCode) {}

		EVENT_CLASS_NAME_AND_TYPE(MouseButtonRelease)

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "MouseButtonReleasedEvent: mouse button code = " << m_mouseButtonCode;

			return ss.str();
		}
	};

	class FILBERT_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y) : m_x(x), m_y(y) {}

		EVENT_CLASS_NAME_AND_TYPE(MouseMove)
		EVENT_CLASS_CATEGORIES(EventCategoryInput | EventCategoryMouse)

		std::pair<float, float> GetCoordinates() const { return { m_x, m_y }; }
		float GetXCoordinate() const { return m_x; }
		float GetYCoordinate() const { return m_y; }

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "MouseMovedEvent: x coordinate = " << m_x << ", y coordinate = " << m_y;

			return ss.str();
		}

	private:
		float m_x = 0.0f, m_y = 0.0f;
	};

	class FILBERT_API MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x, float y) : m_x(x), m_y(y) {}

		EVENT_CLASS_NAME_AND_TYPE(MouseScroll)
		EVENT_CLASS_CATEGORIES(EventCategoryInput | EventCategoryMouse)

		std::pair<float, float> GetOffsets() const { return { m_x, m_y }; }
		float GetXOffset() const { return m_x; }
		float GetYOffset() const { return m_y; }

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "MouseScrolledEvent: x offset = " << m_x << ", y offset = " << m_y;

			return ss.str();
		}

	private:
		float m_x = 0.0f, m_y = 0.0f; // Some mice have horizontal scrolling
	};
}
