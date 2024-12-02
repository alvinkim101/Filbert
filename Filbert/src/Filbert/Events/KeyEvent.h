#pragma once

#include "Event.h"

namespace Filbert
{
	class KeyEvent : public Event
	{
	public:
		int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORIES(EventCategoryInput | EventCategoryKeyboard)

	protected:
		KeyEvent(int keyCode) : m_keyCode(keyCode) {}

		int m_keyCode = 0;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keyCode, bool repeated) : KeyEvent(keyCode), m_repeated(repeated) {}

		EVENT_CLASS_NAME_AND_TYPE(KeyPress)

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "KeyPressedEvent: key code = " << m_keyCode << ", repeated = " << m_repeated;

			return ss.str();
		}

	private:
		bool m_repeated = false;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keyCode) : KeyEvent(keyCode) {}

		EVENT_CLASS_NAME_AND_TYPE(KeyRelease)

		std::string Info() const override
		{
			std::stringstream ss;

			ss << "KeyReleasedEvent: key code = " << m_keyCode;

			return ss.str();
		}
	};
}
