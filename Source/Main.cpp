#include <iostream>

#include "Events/Event.h"
#include "Events/EventDispatcher.h"

// Should be a singleton
static EventDispatcher eventDispatcher;

class TestObserver
{
public:
	void OnInit()
	{
		// Bind the function
		eventDispatcher.Subscribe(TestEvent::descriptor, BIND_EVENT_FN(&TestObserver::OnEventHandle, this));
	}

	void OnEventHandle(const Event& event)
	{
		if (event.GetType() == TestEvent::descriptor)
		{
			const TestEvent& testEvent = static_cast<const TestEvent&>(event);
			std::cout << __FUNCTION__ << ":" << testEvent.GetType() << std::endl;
		}
	}
};

class CustomWindow
{
public:
	void OnEventHandle(const Event& event)
	{
		if (event.GetType() == "CustomWindowEvent")
		{
			const CustomWindowEvent& customWindowEvent = static_cast<const CustomWindowEvent&>(event);
			std::cout << __FUNCTION__ << ":" << customWindowEvent.GetType() << std::endl;

			// Get the width and height of the window
			std::cout << "Width: " << customWindowEvent.m_data.width << " -- " << "Height: " << customWindowEvent.m_data.height << std::endl;
		}
	}
};

int main()
{
	TestObserver testObs;
	testObs.OnInit();

	CustomWindow customWindow;
	// Subscription outside of class
	eventDispatcher.Subscribe(CustomWindowEvent::descriptor, BIND_EVENT_FN(&CustomWindow::OnEventHandle, customWindow));

	eventDispatcher.Broadcast(TestEvent()); // this should call the function OnEventHandle inside the Test Observer class
	eventDispatcher.Broadcast(CustomWindowEvent(1920, 1080));

	return 0;
}