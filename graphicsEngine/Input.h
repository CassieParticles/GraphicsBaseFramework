#pragma once
#include "Window.h"

class GLFWwindow;

class Input
{
public:
	Input(Window* window);
	Input(Input& other) = delete;	//No copy constructor, should only be one input
	Input(Input&& other);
	~Input();

	//Key is currently held down
	bool getKeyDown(int key) { return keysCurrent[key]; }
	//Key is currently not held down
	bool getKeyUp(int key) { return !keysCurrent[key]; }
	//Key was pressed down this frame
	bool getKeyPressed(int key) { return keysCurrent[key] && !keysPrevious[key]; }
	//Key was released this frame
	bool getKeyReleased(int key) { return !keysCurrent[key] && keysPrevious[key]; }

	//Update input
	void Update();

protected:
	friend void Window::UpdateF(Input& input);
	Window* window;
	//Ensure only one instance exists
	static bool instantiated;

	//These are raw pointers to arrays, allows arrays to be swapped easier
	//using std::move on a std::array is O(n), which is suboptimal, faster to just swap the pointers
	bool* keysCurrent;
	bool* keysPrevious;

	//TODO: Add input for mouse
	//TODO: Add input for joysticks
};