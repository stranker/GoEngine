#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* window;
protected:
	int width;
	int height;
	const char* title;
public:
	bool init();
	bool free();
	void pool_events();
	Window(int _width, int _height, const char* _title);
	~Window();
};

