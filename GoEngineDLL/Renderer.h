#pragma once

#include "Window.h"

using namespace std;

class Renderer
{
private:
	Window* window;
	GLuint vertexArrayId;
public:
	enum Primitive {
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005,
	};
	bool Init();
	bool Destroy();
	GLuint CreateVertexBuffer(float *data, size_t dataSize);
	void BindBuffer(GLuint attributeId, GLuint bufferID, size_t dataCount);
	void SetClearColor(float r, float g, float b, float a);
	void ClearScreen();
	void SwapBuffers();
	void EnableBuffer(size_t attributeID);
	void DisableBuffer(size_t attributeID);
	void DeleteBuffer(GLuint bufferID);
	void Draw(Primitive _primitive, int vertexCount);
	Renderer(Window* _window);
	virtual ~Renderer();
};

