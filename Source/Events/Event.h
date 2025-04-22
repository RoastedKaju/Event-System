#pragma once

#include <cstdint>
#include <functional>
#include <vector>
#include <unordered_map>
#include <string>

#include "UtilMacros.h"

namespace EventSystem
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	* @brief Container for event argument data and type safe access
	* 
	* This union based custom variant allows storing different argument types
	* while maintaining type safety through Type enum.
	*/
	struct EventArgument
	{
		/**
		* @brief Enumeration of supported argument types
		*/
		enum class Type
		{
			Integer,
			Float,
			Boolean,
			StringId,
			Count			///< Sentinel value for type validation
		};

		Type m_type;		///< Type of stored argument

		union
		{
			int32_t m_asInteger;
			float m_asFloat;
			bool m_asBool;
			size_t m_asStringId;
		};
	};

	/**
	* @brief Converts integer into event argument
	* 
	* @param value Integer value
	*/
	inline EventArgument MakeArgument(int value)
	{
		EventArgument arg;
		arg.m_type = EventArgument::Type::Integer;
		arg.m_asInteger = value;
		return arg;
	}

	/**
	* @brief Converts float into event argument
	*
	* @param value Float value
	*/
	inline EventArgument MakeArgument(float value)
	{
		EventArgument arg;
		arg.m_type = EventArgument::Type::Float;
		arg.m_asFloat = value;
		return arg;
	}

	/**
	* @brief Converts bool into event argument
	*
	* @param value Boolean value
	*/
	inline EventArgument MakeArgument(bool value)
	{
		EventArgument arg;
		arg.m_type = EventArgument::Type::Boolean;
		arg.m_asBool = value;
		return arg;
	}

	/**
	* @brief Converts string into event argument
	*
	* @param string String value which will be hashed first
	*/
	inline EventArgument MakeArgument(const std::string& string)
	{
		// Hash the string first
		std::hash<std::string> hasher;

		EventArgument arg;
		arg.m_type = EventArgument::Type::StringId;
		arg.m_asStringId = hasher(string);
		return arg;
	}

	/**
	* @brief Container for Event data
	* 
	* Information related to event like event type (Window Resize, Mouse Clicked etc)
	* Number of arguments the event has and the array containing the arguments
	*/
	struct Event
	{
		static constexpr uint32_t MAX_ARGS = 8;

		EventType m_type;
		uint32_t m_numArgs;
		EventArgument m_args[MAX_ARGS];
	};

	template<typename... Args>
	inline std::array<EventArgument, Event::MAX_ARGS> BuildEventArguments(uint32_t outCount, Args&&... args)
	{
		std::array<EventArgument, Event::MAX_ARGS> result;
		outCount = 0;

		auto pack = { (result[outCount++] = MakeArgument(std::forward<Args>(args)), 0)... };
		UNUSED(pack);

		return result;
	}

	using EventHandler = std::function<void(const Event&)>; ///< Naming alias for function pointer

	class EventDispatcher
	{
	public:
		void AddListener(EventType type, EventHandler handler)
		{
			m_listeners[type].push_back(handler);
		}

		void Broadcast(const Event& event)
		{
			auto itr = m_listeners.find(event.m_type);
			if (itr != m_listeners.end())
			{
				// Loop over the vector and call the functions by passing in event
				for (const auto& handler : itr->second)
				{
					handler(event);
				}
			}
		}

	private:
		std::unordered_map<EventType, std::vector<EventHandler>> m_listeners;
	};
}