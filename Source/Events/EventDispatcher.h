#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "Event.h"

namespace SimpleEvent
{
	class EventDispatcher
	{
	public:
		using FunctionType = std::function<void(Event&)>;

		/**
		* @brief Subscribes the event and it's callback
		* 
		* @return Returns the unique ID for the subscription later used to unsubscribe
		*/
		size_t Subscribe(const EventType& type, FunctionType&& function);

		bool Unsubscribe(const EventType& type, size_t id);

		// Using this any client can send events to all observers that are intrested in them.
		void Broadcast(Event& event) const;

	protected:
		std::unordered_map<EventType, std::vector<std::pair<size_t, FunctionType>>> m_observers;

		/// Store unique ID for each subscription so we can remove it later.
		size_t m_nextId = 1;
	};

	/**
	* @brief A handle class for subscriptions, based on RAII
	*/
	class SubscriptionHandle
	{
	public:
		SubscriptionHandle() = default;

		// Subscriptions cannot be copied, they are move only
		SubscriptionHandle(const SubscriptionHandle&) = delete;
		SubscriptionHandle& operator=(const SubscriptionHandle&) = delete;
	};
}