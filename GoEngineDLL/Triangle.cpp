#include "Triangle.h"

void Triangle::Draw() {
	if (material) {
		UseMaterial(); // Uso el material
		material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform())); // Seteo al material la propiedad mvp obtenida por la Camara al shader
	}

	renderer->BindVertexArray(vertexArrayID);

	renderer->BindBuffer(positionBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer posicion del tipo GL_ARRAY_BUFFER
	renderer->SetAttributePointer(0, 3); // Seteo los atributos del vertice de posicion
	
	renderer->BindBuffer(colorBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer posicion del tipo GL_ARRAY_BUFFER
	renderer->SetAttributePointer(1, 4); // Seteo los atributos del vertice de color

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
	CreateVertexArrayID();
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 3);
	SetColorVertex(color_vertex_data, sizeof(color_vertex_data));
	primitive = Renderer::TRIANGLES;
	SetScale(100.0f, 100.0f, 0.0f);
}


Triangle::~Triangle() {
}
