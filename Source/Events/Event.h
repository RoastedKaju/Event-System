#pragma once

#include <iostream>

#define BIND_EVENT_FN(fn, obj) std::bind(fn, obj, std::placeholders::_1)

/**
 * @brief A simple Event interface
 */
class Event
{
public:
	virtual ~Event() = default;

	using DescriptorType = const char*;

	virtual DescriptorType GetType() const = 0;
};

/**
 * @brief A sample event used for testing.
 */
class TestEvent : public Event
{
public:
	TestEvent() {}
	virtual ~TestEvent() {}

	static constexpr DescriptorType descriptor = "TestEvent";

	virtual DescriptorType GetType() const override
	{
		return descriptor;
	}
};

/**
 * @brief A sample windows event used for testing.
 */
class CustomWindowEvent : public Event
{
public:
	CustomWindowEvent() {}
	CustomWindowEvent(unsigned int width, unsigned int height)
	{
		m_data.width = width;
		m_data.height = height;
	}
	virtual ~CustomWindowEvent() {}

	static constexpr DescriptorType descriptor = "CustomWindowEvent";

	virtual DescriptorType GetType() const override
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