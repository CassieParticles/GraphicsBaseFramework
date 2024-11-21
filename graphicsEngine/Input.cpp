#include "Input.h"

#include <graphicsEngine/Window.h>

#include <iostream>
#include <glfw3.h>

bool Input::instantiated = false;

Input::Input(Window* window)
{
	this->window = window;
	keysCurrent = new bool[GLFW_KEY_LAST];
	keysPrevious = new bool[GLFW_KEY_LAST];
}

Input::Input(Input&& other)
{
	window = other.window;
	keysCurrent = other.keysCurrent;
	keysPrevious = other.keysPrevious;
}

Input::~Input()
{
	delete[] keysCurrent;
	delete[] keysPrevious;
}

void Input::Update()
{
	glfwPollEvents();

	//Swap arrays, so previous array stores prior frame's key states
	std::swap(keysCurrent, keysPrevious);

	//Update current keys
	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		keysCurrent[i] = glfwGetKey(window->getWindow(), i);
	}

	//Get mouse position
	if (mouseCentred)
	{
		//Get delta position
		double mouseX, mouseY;
		glfwGetCursorPos(window->getWindow(), &mouseX, &mouseY);
		mousePositionX = mouseX - window->getWidth();
		mousePositionY = mouseY - window->getHeight();
		glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
	}
	else
	{
		glfwGetCursorPos(window->getWindow(), &mousePositionX, &mousePositionY);
	}

	mousePositionX = min(max(0, mousePositionX), window->getWidth());
	mousePositionY = min(max(0, mousePositionY), window->getHeight());

}


