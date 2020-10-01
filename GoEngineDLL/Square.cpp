#include "Square.h"


void Square::Draw() {
	if (material) {
		UseMaterial(); // Uso el material
		material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
	}
	renderer->BindBuffer(0, positionBuffer, 3); // Bindeo  y activo el atributo ID (pos) del shader, pos buffer ID, 3 puntos
	renderer->BindBuffer(1, colorBuffer, 4); // bindeo y activo el atributo ID (color), color buffer ID, 4 (RGBA)
	renderer->Draw(primitive, positionVertexCount); // Dibujo el triangulo
	renderer->DisableBuffer(0); // Deshabilito los atributos (pos)
	renderer->DisableBuffer(1); // Deshabilito los atributos (color)
}

Square::Square(Renderer *_renderer) : Shape(_renderer) {
	float position_vertex_data[] = {
		// first triangle
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left 
		// second triangle
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	};
	float color_vertex_data[] = {
		0.2f, 0.0f, 0.0f, 1.0f,
		0.0f, 4.0f, 0.0f, 1.0f,
		0.0f, 0.3f, 0.5f, 1.0f,
		1.0f, 0.0f, 0.7f, 1.0f,
		0.0f, 2.0f, 0.1f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
	};
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 6);
	SetColorVertex(color_vertex_data,sizeof(color_vertex_data));
	primitive = Renderer::TRIANGLES;
	SetScale(100, 100, 0);
}


Square::~Square() {
}
