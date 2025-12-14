#pragma once

#include <iostream>

#define BIND_EVENT_FN(fn, obj) std::bind(fn, obj, std::placeholders::_1)

namespace SimpleEvent
{
	enum class EventType
	{
		WindowResize, WindowClose, WindowMaximize, WindowMinimize,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved
	};

	/**
	 * @brief A simple Event interface
	 *
	 */
	class Event
	{
	public:
		virtual ~Event() = default;

		//using DescriptorType = const char*;

		virtual EventType GetType() const = 0;

		virtual bool IsHandled() const { return m_isHandled; };
		virtual void SetIsHandled(bool value) { m_isHandled = value; };

		virtual const std::string& GetName() const { return m_debugName; }

	protected:
		bool m_isHandled = false;
		std::string m_debugName = "";
	};

	/**
	 * @brief A sample event used for testing.
	 */
	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent() { m_debugName = "MouseButtonPressedEvent"; }
		virtual ~MouseButtonPressedEvent() {}

		static constexpr EventType descriptor = EventType::MouseButtonPressed;

		virtual EventType GetType() const override
		{
			return descriptor;
		}
	};

	/**
	 * @brief A sample windows event used for testing.
	 */
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent() { m_debugName = "WindowResizeEvent"; }
		WindowResizeEvent(unsigned int width, unsigned int height)
		{
			m_data.width = width;
			m_data.height = height;
			m_debugName = "WindowResizeEvent";
		}
		virtual ~WindowResizeEvent() {}

		static constexpr EventType descriptor = EventType::WindowResize;

		virtual EventType GetType() const override
		{
			return descriptor;
		}

		// You can store data here inside of a custom struct
		// And reterive it inside the 'OnHandleEvent' of your observer class
		struct {
			unsigned int width = 800;
			unsigned int height = 600;
		} m_data;
	};
}

