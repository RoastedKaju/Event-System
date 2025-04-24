#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>

#include "Events/Event.h"

//static EventSystem::EventDispatcher s_dispatcher;

class ExampleWindow
{
public:
	ExampleWindow()
	{

	}

	void SimulateMouseButtonPressed(int mouseButtonKeycode)
	{
		BROADCAST_GLOBAL(EventSystem::EventType::MouseButtonPressed, mouseButtonKeycode);
	}

	void SimulateMouseButtonReleased(int mouseButtonKeycode)
	{
		BROADCAST_GLOBAL(EventSystem::EventType::MouseButtonReleased, mouseButtonKeycode, "Haris", 15.5f);
	}
};


class ExampleApplication
{
public:
	ExampleApplication()
	{
		// Create a listener for mouse clicks
		ADD_LISTENER_GLOBAL(EventSystem::EventType::MouseButtonPressed, [this](const EventSystem::Event& event) {OnMouseButton(event); });
		ADD_LISTENER_GLOBAL(EventSystem::EventType::MouseButtonReleased, [this](const EventSystem::Event& event) {OnMouseButton(event); });
	}

	void OnMouseButton(const EventSystem::Event& event)
	{
		if (event.m_type == EventSystem::EventType::MouseButtonPressed)
		{
			std::cout << "Recieved On Mouse Button Pressed Event Inside Application Object." << std::endl;
			std::cout << "Keycode is: " << event.m_args[0].m_asInteger << std::endl;
			std::cout << m_data << std::endl;
		}
		else if (event.m_type == EventSystem::EventType::MouseButtonReleased)
		{
			std::cout << "Recieved On Mouse Button Released Event Inside Application Object." << std::endl;
			std::cout << "Keycode is: " << event.m_args[0].m_asInteger << std::endl;
			std::cout << "String ID is: " << event.m_args[1].m_asStringId << std::endl;
			std::cout << "Float is: " << event.m_args[2].m_asFloat << std::endl;
		}
	}

private:
	float m_data = 50.0f;
};