#pragma once

#include <iostream>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "event.h"

namespace SimpleEvent
{
	class SubscriptionHandle; // forward declare

	class EventDispatcher
	{
	public:
		EventDispatcher(const EventDispatcher&) = delete;
		EventDispatcher(EventDispatcher&&) = delete;
		EventDispatcher& operator=(const EventDispatcher&) = delete;
		EventDispatcher& operator=(EventDispatcher&&) = delete;

		using FunctionType = std::function<void(Event&)>;

		static EventDispatcher& Get()
		{
			static EventDispatcher instance;
			return instance;
		}

		/**
		* @brief Subscribes the event and it's callback
		* 
		* @return Returns the unique ID for the subscription later used to unsubscribe
		*/
		size_t Subscribe(const EventType& type, FunctionType&& function);

		SubscriptionHandle SubscribeRAII(const EventType& type, FunctionType&& function);

		bool Unsubscribe(const EventType& type, size_t id);

		// Using this any client can send events to all observers that are intrested in them.
		void Broadcast(Event& event) const;

	protected:
		std::unordered_map<EventType, std::vector<std::pair<size_t, FunctionType>>> m_observers;

		/// Store unique ID for each subscription so we can remove it later.
		size_t m_nextId = 1;

	private:
		// This forces users to call the EventDispatcher::Get()
		EventDispatcher() = default;
	};

	/**
	* @brief A handle class for subscriptions, based on RAII
	*/
	class SubscriptionHandle
	{
	public:
		SubscriptionHandle() = default;
		SubscriptionHandle(EventType type, size_t id) : m_type{ type }, m_id{ id } {};

		~SubscriptionHandle()
		{
			std::cout << "Unsubscribed Event ID:" << m_id << std::endl;
			Unsubscribe();
		}

		// Subscriptions cannot be copied, they are move only
		SubscriptionHandle(const SubscriptionHandle&) = delete;
		SubscriptionHandle& operator=(const SubscriptionHandle&) = delete;
		
		inline void Unsubscribe() { EventDispatcher::Get().Unsubscribe(m_type, m_id); }
	private:
		EventType m_type;
		size_t m_id = 0;
	};
}