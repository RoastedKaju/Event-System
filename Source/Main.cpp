#include "ExampleCode.h"

#include <stdio.h>
#include <iostream>

int main()
{
	// Create Application Object
	ExampleApplication* app = new ExampleApplication();
	// Create Windows Object
	ExampleWindow* window = new ExampleWindow();

	window->SimulateMouseButtonPressed(52);
	window->SimulateMouseButtonReleased(12);

	// Clean up
	delete window;
	delete app;

	std::cout << "Hello World!" << std::endl;
	return EXIT_SUCCESS;
}