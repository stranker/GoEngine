#include "Triangle.h"

void Triangle::Draw() {
	if (material) {
		UseMaterial(); // Uso el material
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(0, positionBuffer, positionVertexCount); // Bindeo  y activo el atributo ID (pos), pos ID, 3 puntos
	renderer->BindBuffer(1, colorBuffer, colorVertexCount); // bindeo y activo el atributo ID (color), color ID, 4 (RGBA)
	renderer->Draw(positionVertexCount); // Dibujo el triangulo
	renderer->DisableBuffer(0); // Deshabilito los atributos (pos)
	renderer->DisableBuffer(1); // Deshabilito los atributos (color)
}

Triangle::Triangle(Renderer* _renderer) : Shape(_renderer) {
	float position_vertex_data[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	float color_vertex_data[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), positionVertexCount);
	SetColorVertex(color_vertex_data, sizeof(color_vertex_data), colorVertexCount);
}


Triangle::~Triangle() {
}