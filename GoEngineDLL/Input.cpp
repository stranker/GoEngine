#include "Input.h"

Window *Input::window = NULL;

bool Input::IsKeyPressed(KeyCode key) {
	return glfwGetKey(window->GetWindowPtr(), key) == KEY_PRESSED;
}

void Input::SetWindow(Window * _window) {
	window = _window;
}

Input::Input(){
}


Input::~Input() {
}
