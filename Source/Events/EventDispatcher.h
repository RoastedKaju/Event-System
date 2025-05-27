#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Event.h"

class EventDispatcher
{
public:
	using FunctionType = std::function<void(const Event&)>;

	void Subscribe(const Event::DescriptorType& type, FunctionType&& function);

	// Using this any client can send events to all observers that are intrested in them.
	void Broadcast(const Event& event) const;

protected:
	std::unordered_map<Event::DescriptorType, std::vector<FunctionType>> m_observers;
};