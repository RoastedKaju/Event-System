#include <iostream>

#include "Events/Event.h"
#include "Events/EventDispatcher.h"

using namespace SimpleEvent;

// Should be a singleton
static EventDispatcher eventDispatcher;

class MouseInput
{
public:
	size_t OnInit()
	{
		// Bind the function
		return eventDispatcher.Subscribe(MouseButtonPressedEvent::descriptor, BIND_EVENT_FN(&MouseInput::OnEventHandle, this));
	}

	void OnEventHandle(Event& event)
	{
		if (event.GetType() == MouseButtonPressedEvent::descriptor)
		{
			MouseButtonPressedEvent& mousePressedEvent = static_cast<MouseButtonPressedEvent&>(event);
			std::cout << __FUNCTION__ << ":" << mousePressedEvent.GetName() << std::endl;
			mousePressedEvent.SetIsHandled(false); // Setting this to true means it wont propagate to other layers
		}
	}
};

/**
* @brief An example layer, it subscribes to the same event as mouse input but if it is handled first the event won't propagate to this layer
*
*/
class AnotherLayer
{
public:
	void OnInit()
	{
		// Bind the function
		eventDispatcher.Subscribe(MouseButtonPressedEvent::descriptor, BIND_EVENT_FN(&AnotherLayer::OnEventHandle, this));
	}

	void OnEventHandle(Event& event)
	{
		if (event.GetType() == MouseButtonPressedEvent::descriptor)
		{
			MouseButtonPressedEvent& mousePressedEvent = static_cast<MouseButtonPressedEvent&>(event);
			std::cout << __FUNCTION__ << ":" << mousePressedEvent.GetName() << std::endl;
		}
	}
};

class CustomWindow
{
public:
	void OnEventHandle(Event& event)
	{
		if (event.GetType() == EventType::WindowResize)
		{
			const WindowResizeEvent& customWindowEvent = static_cast<const WindowResizeEvent&>(event);
			std::cout << __FUNCTION__ << ":" << customWindowEvent.GetName() << std::endl;

			// Get the width and height of the window
			std::cout << "Width: " << customWindowEvent.m_data.width << " -- " << "Height: " << customWindowEvent.m_data.height << std::endl;

			for (const auto name : names)
			{
				std::cout << name << std::endl;
			}
		}
	}

private:
	// Random object owned data for testing purposes
	std::vector<std::string> names{ "A", "B", "C" };
};

int main()
{
	MouseInput mouseObj;
	mouseObj.OnInit();
	AnotherLayer anotherLayer;
	anotherLayer.OnInit();

	// Pointer to test if data is valid on callback if object deleted first.
	CustomWindow* customWindow = new CustomWindow{};
	// Subscription outside of class
	auto eventHandle = eventDispatcher.Subscribe(WindowResizeEvent::descriptor, BIND_EVENT_FN(&CustomWindow::OnEventHandle, customWindow));
	eventDispatcher.Unsubscribe(WindowResizeEvent::descriptor, eventHandle); // Make sure to unsubscribe events before deleting the object
	delete customWindow;

	eventDispatcher.Broadcast(MouseButtonPressedEvent()); // this should call the function OnEventHandle inside the Test Observer class
	eventDispatcher.Broadcast(WindowResizeEvent(1920, 1080));

	return 0;
}