#include "EventDispatcher.h"

void EventDispatcher::Subscribe(const EventType& type, FunctionType&& function)
{
	m_observers[type].push_back(function);
}

void EventDispatcher::Broadcast(Event& event) const
{
	auto type = event.GetType();

	if (m_observers.find(type) == m_observers.end())
	{
		// No registered functions for this event type found.
		return;
	}

	auto&& observers = m_observers.at(type);

	for (auto&& observer : observers)
	{
		if (event.IsHandled())
		{
			break;
		}
		// Call the function using the event you got in parameter
		observer(event);
	}
}
