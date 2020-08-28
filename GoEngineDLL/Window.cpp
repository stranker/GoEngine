#include "Window.h"

bool Window::init()
{
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
	return true;

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	

}

bool Window::free()
{
	if (window != NULL) {
		glfwDestroyWindow((GLFWwindow*)window);
	}
	window = NULL;
	glfwTerminate();
	return true;
}

void Window::pool_events(){
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

Window::Window(int _width, int _height, const char * _title){
	width = _width;
	height = _height;
	title = _title;
}

Window::~Window(){

}
