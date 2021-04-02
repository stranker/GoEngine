#pragma once

#include "Exports.h"
#include "Utils.h"
#include <iostream>

class GLFWwindow;

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
	static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void OnMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	bool Init();
	bool Destroy();
	void PoolEvents();
	bool ShouldClose();
	void CloseWindow();
	float GetWidth() const;
	float GetHeight() const;
	Vector2 GetSize() const;
	void* GetWindowPtr();

	static Window* GetSingleton();
	Window(int _width, int _height, const char* _title);
	~Window();
};

