#include "Triangle.h"

void Triangle::Draw() {
	if (material) {
		material->Use(); // Uso el material
		material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform())); // Seteo al material la propiedad mvp obtenida por la Camara al shader
	}
	renderer->Draw(GetVertexArrayID(), primitive, 3);
}

void Triangle::Destroy() {

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
	CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0);
	CreateVertexData(color_vertex_data, sizeof(color_vertex_data), 4, Renderer::ARRAY_BUFFER, 1);
	primitive = Renderer::TRIANGLES;
}


Triangle::~Triangle() {
}
