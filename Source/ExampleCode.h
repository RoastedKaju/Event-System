#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>

#include "Events/Event.h"

static EventSystem::EventDispatcher s_dispatcher;

class ExampleWindow
{
public:
	ExampleWindow()
	{

	}

	void SimulateMouseButtonPressed(int mouseButtonKeycode)
	{
		EventSystem::Event mouseEvent;
		mouseEvent.m_type = EventSystem::EventType::MouseButtonPressed;
		mouseEvent.m_numArgs = 1;
		mouseEvent.m_args[0] = EventSystem::MakeArgument(mouseButtonKeycode);

		s_dispatcher.Broadcast(mouseEvent);
	}
};


class ExampleApplication
{
public:
	ExampleApplication()
	{
		// Create a listener for mouse clicks
		s_dispatcher.AddListener(EventSystem::EventType::MouseButtonPressed, [this](const EventSystem::Event& event) { OnMouseButtonPressed(event); });
	}

	void OnMouseButtonPressed(const EventSystem::Event& event)
	{
		if (event.m_type == EventSystem::EventType::MouseButtonPressed)
		{
			std::cout << "Recieved On Mouse Button Pressed Event Inside Application Object." << std::endl;
			std::cout << "Keycode is: " << event.m_args[0].m_asInteger << std::endl;
		}
	}
};