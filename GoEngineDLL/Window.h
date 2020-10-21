#pragma once

#include "Exports.h"
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <iostream>
#include "Vector2.h"

using namespace std;

class ENGINEDLL_API Window
{
private:
	GLFWwindow* window;
	static Window* singleton;
protected:
	int width;
	int height;
	const char* title;
public:
	bool Init();
	bool Destroy();
	void PoolEvents();
	bool ShouldClose();
	void CloseWindow();
	float GetWidth() const;
	float GetHeight() const;
	Vector2 GetSize() const;
	GLFWwindow* GetWindowPtr();
	static Window* GetSingleton();
	Window(int _width, int _height, const char* _title);
	~Window();
};

