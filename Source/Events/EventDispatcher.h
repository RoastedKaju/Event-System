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
	using FunctionType = std::function<void(Event&)>;

	void Subscribe(const EventType& type, FunctionType&& function);

	// Using this any client can send events to all observers that are intrested in them.
	void Broadcast(Event& event) const;

protected:
	std::unordered_map<EventType, std::vector<FunctionType>> m_observers;
};