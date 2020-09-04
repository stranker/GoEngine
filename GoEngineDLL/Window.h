#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>

using namespace std;

class Window
{
private:
	GLFWwindow* window;
protected:
	int width;
	int height;
	const char* title;
public:
	bool Init();
	bool Destroy();
	void PoolEvents();
	bool ShouldClose();
	GLFWwindow* GetWindowPtr();
	Window(int _width, int _height, const char* _title);
	~Window();
};

