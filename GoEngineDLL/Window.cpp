#include "Window.h"

bool Window::init()
{
	fprintf(stderr, "Windows init");
	/* Initialize the library */
	if (!glfwInit()) {
		fprintf(stderr, "Falla al inicialiar GLFW\n");
		getchar();
		return false;
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window){
		fprintf(stderr, "Falla al crear Window\n");
		getchar();
		glfwTerminate();
		return false;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	return true;	
}

bool Window::free()
{
	fprintf(stderr, "Windows free");
	if (window != NULL) {
		glfwDestroyWindow((GLFWwindow*)window);
	}
	window = NULL;
	glfwTerminate();
	return true;
}

void Window::pool_events(){
	glfwPollEvents();
}

void Window::set_clear_color(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void Window::clear_color(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap_buffers(){
	glfwSwapBuffers(window);
}

bool Window::should_close(){
	return glfwWindowShouldClose(window);
}

Window::Window(int _width, int _height, const char * _title){
	width = _width;
	height = _height;
	title = _title;
}

Window::~Window(){

}
