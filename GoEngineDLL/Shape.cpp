#include "Shape.h"



GLuint Shape::CreateTriangleBuffer()
{
	float triangle_vertex_data[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,   // top 
	};
	GLuint vertexBuffer = renderer->CreateVertexBuffer(triangle_vertex_data, sizeof(triangle_vertex_data));
	// Positions
	renderer->BindBuffer(0, 3, 7, 0);
	// Colors
	renderer->BindBuffer(1, 4, 7, 3);
	return vertexBuffer;
}

void Shape::Draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

Shape::Shape(Renderer* _renderer)
{
	SetRenderer(_renderer);
}


Shape::~Shape()
{
}
