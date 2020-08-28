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
	void set_clear_color(float r, float g, float b, float a);
	void clear_color();
	void swap_buffers();
	bool should_close();
	Window(int _width, int _height, const char* _title);
	~Window();
};

