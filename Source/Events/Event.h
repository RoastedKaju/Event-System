#pragma once

#include <iostream>

#define BIND_EVENT_FN(x) std::cout << "Unimplemented" << std::endl;

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