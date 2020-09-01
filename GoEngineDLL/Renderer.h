#pragma once
#include "GL/glew.h"

class Renderer
{
private:
	GLuint vertexArrayId;
	GLuint vertexBuffer;
public:
	GLuint GetVertexBuffer() { return vertexBuffer; };

	void GenerateVertexArray();
	void BindVertexArray();
	void GenerateBuffer();
	void BindBuffer();
	void GenerateBufferData();
	Renderer();
	~Renderer();
};

