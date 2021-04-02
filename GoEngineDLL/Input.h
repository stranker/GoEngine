#pragma once
#include "Exports.h"
#include <iostream>

class Window;
class Vector2;
class GLFWwindow;

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

	enum KeyCode {
		KEY_0 = 48,
		KEY_1 = 49,
		KEY_2 = 50,
		KEY_3 = 51,
		KEY_A = 65,
		KEY_D = 68,
		KEY_E = 69,
		KEY_Q = 81,
		KEY_S = 83,
		KEY_W = 87,
		KEY_ESCAPE = 256,
		KEY_ENTER = 257,
		KEY_RIGHT = 262,
		KEY_LEFT = 263,
		KEY_DOWN = 264,
		KEY_UP = 265,
	};

	enum MouseButton {
		MOUSE_BUTTON_1 = 0,
		MOUSE_BUTTON_2 = 1,
		MOUSE_BUTTON_3 = 2
	};

	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	static Vector2 GetMousePosition();
	static bool IsMouseButtonPressed(MouseButton button);
	static bool IsKeyPressed(KeyCode key);
	Input(Window* window);
	virtual ~Input();
};

