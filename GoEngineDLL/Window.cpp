#include "Window.h"

bool Window::Init()
{
	cout << "Windows Init" << endl;
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
	return true;
}

bool Window::Destroy(){
	cout << "Windows Destroy" << endl;
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

GLFWwindow* Window::GetWindowPtr(){
	return window;
}

Window::Window(int _width, int _height, const char * _title){
	width = _width;
	height = _height;
	title = _title;
}

Window::~Window(){

}
