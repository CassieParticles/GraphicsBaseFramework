#include "Input.h"
#include "Input.h"

#include <graphicsEngine/Window.h>

#include <iostream>
#include <GLFW/glfw3.h>

bool InputHandler::instantiated = false;

InputHandler::InputHandler(Window* window)
{
	this->window = window;
	keysCurrent = new bool[GLFW_KEY_LAST];
	keysPrevious = new bool[GLFW_KEY_LAST];

	mouseCurrent = new bool[GLFW_MOUSE_BUTTON_LAST];
	mousePrevious = new bool[GLFW_MOUSE_BUTTON_LAST];
}

InputHandler::InputHandler(InputHandler&& other)
{
	window = other.window;
	keysCurrent = other.keysCurrent;
	keysPrevious = other.keysPrevious;

	mouseCurrent = other.mouseCurrent;
	mousePrevious = other.mousePrevious;

	mousePositionX = other.mousePositionX;
	mousePositionY = other.mousePositionY;

	mouseCentred = other.mouseCentred;
}

InputHandler::~InputHandler()
{
	delete[] keysCurrent;
	delete[] keysPrevious;
}

void InputHandler::setMouseCentred(bool centred)
{
	this->mouseCentred = centred;
	glfwSetInputMode(window->getWindow(), GLFW_CURSOR, centred ? GLFW_CURSOR_HIDDEN: GLFW_CURSOR_NORMAL);
	if (mouseCentred)
	{
		glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
	}
}

void InputHandler::Update()
{
	glfwPollEvents();

	//Swap arrays, so previous array stores prior frame's key states
	std::swap(keysCurrent, keysPrevious);
	std::swap(mouseCurrent, mousePrevious);

	//Update current keys
	for (int i = 0; i < GLFW_KEY_LAST; ++i)
	{
		keysCurrent[i] = glfwGetKey(window->getWindow(), i);
	}

	//Update current mouse positions
	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; ++i)
	{
		mouseCurrent[i] = glfwGetMouseButton(window->getWindow(), i);
	}

	//Get mouse position
	if (mouseCentred)
	{
		//Get delta position
		double mouseX, mouseY;
		glfwGetCursorPos(window->getWindow(), &mouseX, &mouseY);
		mousePositionX = mouseX - window->getWidth() / 2;
		mousePositionY = mouseY - window->getHeight() / 2;
		glfwSetCursorPos(window->getWindow(), window->getWidth() / 2, window->getHeight() / 2);
	}
	else
	{
		glfwGetCursorPos(window->getWindow(), &mousePositionX, &mousePositionY);

		mousePositionX = min(max(0, mousePositionX), window->getWidth());
		mousePositionY = min(max(0, mousePositionY), window->getHeight());
	}



}


