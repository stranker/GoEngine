#include "Input.h"

bool Input::IsKeyPressed(KeyCode key) {
	return glfwGetKey(window->GetWindowPtr(), key) == KEY_PRESSED;
}

Input::Input(Window *_window) : window(_window){
}


Input::~Input() {
}
