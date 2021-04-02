#include "Input.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

Window *Input::window = NULL;

bool Input::IsKeyPressed(KeyCode key) {
	return glfwGetKey((GLFWwindow*)window->GetWindowPtr(), key) == KEY_PRESSED;
}

void Input::MousePositionCallback(GLFWwindow* _window, double xpos, double ypos) {
	cout << "zalranga" << endl;
	if (_window) {
		cout << "asd" << endl;
	}
}

Vector2 Input::GetMousePosition() {
	double xpos, ypos;
	glfwGetCursorPos((GLFWwindow*)window->GetWindowPtr(), &xpos, &ypos);
	return Vector2(xpos, ypos);
}

bool Input::IsMouseButtonPressed(MouseButton button) {
	return glfwGetMouseButton((GLFWwindow*)window->GetWindowPtr(), button) == KEY_PRESSED;
}

Input::Input(Window* _window){
	window = _window;
	glfwSetCursorPosCallback((GLFWwindow*)_window->GetWindowPtr(), MousePositionCallback);
}

Input::~Input() {
}
