#pragma once
#include "Exports.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

#include "KeyCode.h";

using namespace std;

class ENGINEDLL_API Input {
protected:
	static Window *window;
public:
	enum KeyState {
		KEY_RELEASED = 0,
		KEY_PRESSED = 1,
		KEY_REPEAT = 2,
	};

	static bool IsKeyPressed(KeyCode key);
	void SetWindow(Window* window);
	Input();
	virtual ~Input();
};

