#pragma once
#include "Exports.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

using namespace std;

class ENGINEDLL_API Input {
protected:
	Window *window;
public:
	enum KeyState {
		KEY_RELEASED = 0,
		KEY_PRESSED = 1,
		KEY_REPEAT = 2,
	};
	enum KeyCode {
		KEY_ESCAPE = 256,
		KEY_ENTER = 257,
		KEY_RIGHT = 262,
		KEY_LEFT = 263,
		KEY_DOWN = 264,
		KEY_UP = 265,
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 =  50,
	};
	bool IsKeyPressed(KeyCode key);
	Input(Window *window);
	virtual ~Input();
};

