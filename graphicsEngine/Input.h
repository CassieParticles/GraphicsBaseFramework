#pragma once
#include "Window.h"

class GLFWwindow;

class InputHandler
{
public:
	InputHandler(Window* window);
	InputHandler(InputHandler& other) = delete;	//No copy constructor, should only be one input
	InputHandler(InputHandler&& other);
	~InputHandler();

	//Key is currently held down
	bool getKeyDown(int key) { return keysCurrent[key]; }
	//Key is currently not held down
	bool getKeyUp(int key) { return !keysCurrent[key]; }
	//Key was pressed down this frame
	bool getKeyPressed(int key) { return keysCurrent[key] && !keysPrevious[key]; }
	//Key was released this frame
	bool getKeyReleased(int key) { return !keysCurrent[key] && keysPrevious[key]; }

	double getCursorX() { return mousePositionX; }
	double getCursorY() { return mousePositionY; }

	void setMouseCentred(bool centred) { this->mouseCentred = centred; }
	bool getMouseCentred() { return mouseCentred; }

	//Update input
	void Update();

protected:
	friend void Window::UpdateF(InputHandler& input);
	Window* window;
	//Ensure only one instance exists
	static bool instantiated;

	//These are raw pointers to arrays, allows arrays to be swapped easier
	//using std::move on a std::array is O(n), which is suboptimal, faster to just swap the pointers
	bool* keysCurrent;
	bool* keysPrevious;

	double mousePositionX;
	double mousePositionY;

	bool mouseCentred;
	//TODO: Add input for joysticks
};