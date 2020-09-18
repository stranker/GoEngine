#include "Square.h"


void Square::Draw() {
	if (material) {
		UseMaterial(); // Uso el material
	}
	renderer->EnableBuffer(0);
	renderer->EnableBuffer(1);
	renderer->BindBuffer(0, positionBuffer, positionVertexCount); // Bindeo  y activo el atributo ID (pos), pos ID, 3 puntos
	renderer->BindBuffer(1, colorBuffer, colorVertexCount); // bindeo y activo el atributo ID (color), color ID, 4 (RGBA)
	renderer->Draw(primitive, positionVertexCount); // Dibujo el triangulo
	renderer->DisableBuffer(0); // Deshabilito los atributos (pos)
	renderer->DisableBuffer(1); // Deshabilito los atributos (color)
}

Square::Square(Renderer *_renderer) : Shape(_renderer) {
	float position_vertex_data[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	float color_vertex_data[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};
	primitive = Renderer::TRIANGLE_STRIP;
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 4);
	SetColorVertex(color_vertex_data,sizeof(color_vertex_data), 4);
}


Square::~Square() {
}