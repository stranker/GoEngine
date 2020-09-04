#pragma once

#include "Window.h"

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
	void BindBuffer(GLuint attributeId, uint8_t dataCount, uint8_t dataSize, uint8_t offset);
	GLuint CreateTriangleBuffer();
	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffers();
	void DrawBuffer(uint8_t vertexCount);
	Renderer(Window* _window);
	virtual ~Renderer();
};

