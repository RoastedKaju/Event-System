#include "EventDispatcher.h"

namespace SimpleEvent
{
	size_t EventDispatcher::Subscribe(const EventType& type, FunctionType&& function)
	{
		const size_t id = m_nextId++;
		m_observers[type].emplace_back(id, std::move(function));
		//m_observers[type].push_back(function);
		return id;
	}

	bool EventDispatcher::Unsubscribe(const EventType& type, size_t id)
	{
		auto itr = m_observers.find(type);
		// If no even of this type exists return false
		if (itr == m_observers.end()) return false;

		// Get the vector from observers map which contain ID and Function signature
		auto& id_func_map = itr->second;
		auto pervSize = id_func_map.size(); // Store old size before removal of element

		id_func_map.erase(std::remove_if(id_func_map.begin(),
			id_func_map.end(), [id](const auto& pair) {return pair.first == id; }), id_func_map.end());

		return id_func_map.size() != pervSize;
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

		for (auto&& [id ,observer] : observers)
		{
			if (event.IsHandled())
			{
				break;
			}
			// Call the function using the event you got in parameter
			observer(event);
		}
	}
}