#include "Input.h"
#include "Window.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

Window* Input::window = NULL;
Vector2 Input::mousePosition = Vector2();
Vector2 Input::mouseScroll = Vector2();

bool Input::IsKeyPressed(KeyCode key) {
	return glfwGetKey((GLFWwindow*)window->GetWindowPtr(), key) == KEY_PRESSED;
}

void Input::SetCurrentWindow(Window* _window) {
	window = _window;
	if ((GLFWwindow*)window->GetWindowPtr()) {
		glfwSetCursorPosCallback((GLFWwindow*)window->GetWindowPtr(), OnMousePositionCallback);
		glfwSetScrollCallback((GLFWwindow*)window->GetWindowPtr(), OnMouseScrollCallback);
	}
}

Vector2 Input::GetMousePosition() {
	return Vector2();
}

Vector2 Input::GetMouseScroll() {
	return Vector2();
}

void Input::SetMouseScrollCallback(void* callback) {
	if ((GLFWwindow*)window->GetWindowPtr()) {
		glfwSetScrollCallback((GLFWwindow*)window->GetWindowPtr(), (GLFWscrollfun)callback);
	}
}

void Input::SetMousePositionCallback(void* callback) {
	if ((GLFWwindow*)window->GetWindowPtr()) {
		glfwSetScrollCallback((GLFWwindow*)window->GetWindowPtr(), (GLFWcursorposfun)callback);
	}
}

void Input::OnMousePositionCallback(GLFWwindow* _window, double xpos, double ypos) {
	mousePosition = Vector2(xpos, ypos);
}

void Input::OnMouseScrollCallback(GLFWwindow* _window, double xoffset, double yoffset) {
	mouseScroll = Vector2(xoffset, yoffset);
}

bool Input::IsMouseButtonPressed(MouseButton button) {
	return glfwGetMouseButton((GLFWwindow*)window->GetWindowPtr(), button) == KEY_PRESSED;
}

Input::Input(){
}

Input::~Input() {
}
