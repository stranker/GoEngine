#include "Renderer.h"

void Renderer::GenerateVertexArray()
{
	glGenVertexArrays(1, (&vertexArrayId));
}

void Renderer::BindVertexArray()
{
	glBindVertexArray(vertexArrayId);
}

void Renderer::GenerateBuffer()
{
	glGenBuffers(1, &vertexBuffer);
}

void Renderer::BindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
}

void Renderer::GenerateBufferData()
{

	float g_vertex_buffer_data[] = { //Esto no deberia ir aca, pero cuando lo quiero pasar como dato no me lo toma el glBufferData
		-1.0f, -1.0f, 0.0f,			//Plz halp Natarelli-sama :,c
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}
