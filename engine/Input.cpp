#include "Input.h"

#include <engine/Window.h>

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
}


