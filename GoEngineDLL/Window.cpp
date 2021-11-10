#include "Window.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

bool Window::Init(){
	/* Initialize the library */
	if (!glfwInit()) {
		cout << "Falla al inicialiar GLFW" << endl;
		getchar();
		return false;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window){
		cout << "Falla al crear Window" << endl;
		getchar();
		glfwTerminate();
		return false;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glViewport(0, 0, width, height);
	return true;
}

bool Window::Destroy(){
	if (window) {
		glfwDestroyWindow((GLFWwindow*)window);
	}
	window = NULL;
	glfwTerminate();
	return true;
}

void Window::PoolEvents(){
	glfwPollEvents();
}

bool Window::ShouldClose(){
	return glfwWindowShouldClose(window);
}

void Window::CloseWindow() {
	glfwSetWindowShouldClose(window, true);
}

float Window::GetWidth() const {
	return width;
}

float Window::GetHeight() const {
	return height;
}

Vector2 Window::GetSize() const {
	return Vector2(width, height);
}

void* Window::GetWindowPtr(){
	return (void*)window;
}

Window* Window::singleton = NULL;

Window * Window::GetSingleton() {
	return singleton;
}

Window::Window(int _width, int _height, const char * _title){
	width = _width;
	height = _height;
	title = _title;
	singleton = this;
}

Window::~Window(){
}
