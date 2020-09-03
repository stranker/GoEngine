#pragma once
#include "GL/glew.h"
#include "Window.h"
#include <iostream>

using namespace std;

class Renderer
{
private:
	Window* window;
	GLuint vertexArrayId;
public:
	bool Init();
	bool Destroy();
	GLuint CreateVertexBuffer(float *data, size_t dataSize);
	void BindBuffer(GLuint vertexBuffer, uint8_t size);
	void CreateTriangleBuffer();
	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffers();
	void DrawBuffer(uint8_t vertexCount);
	Renderer(Window* _window);
	virtual ~Renderer();
};

