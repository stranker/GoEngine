#include "Triangle.h"

void Triangle::Draw() {
	if (material) {
		UseMaterial(); // Uso el material
		material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform())); // Seteo al material la propiedad mvp obtenida por la Camara al shader
	}
	renderer->BindBuffer(0, positionBuffer, 3); // Bindeo  y activo el atributo ID (pos), pos ID, 3 puntos
	renderer->BindBuffer(1, colorBuffer, 4); // Bindeo y activo el atributo ID (color), color ID, 4 (RGBA)

	renderer->Draw(primitive, positionVertexCount); // Dibujo el triangulo

	renderer->DisableBuffer(0); // Deshabilito el atributo (pos)
	renderer->DisableBuffer(1); // Deshabilito el atributo (color)
}

Triangle::Triangle(Renderer* _renderer) : Shape(_renderer) {
	float position_vertex_data[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
	float color_vertex_data[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
	};
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 3);
	SetColorVertex(color_vertex_data, sizeof(color_vertex_data));
	primitive = Renderer::TRIANGLES;
	SetScale(100.0f,100.0f,0.0f);
}


Triangle::~Triangle() {
}
