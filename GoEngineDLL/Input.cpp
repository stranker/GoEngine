#include "Input.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

Window *Input::window = NULL;

bool Input::IsKeyPressed(KeyCode key) {
	return glfwGetKey(window->GetWindowPtr(), key) == KEY_PRESSED;
}

Input::Input(Window* _window){
	window = _window;
}


Input::~Input() {
}
