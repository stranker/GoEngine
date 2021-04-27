#include "Square.h"


void Square::Draw() {
	if (material) {
		material->Use(); // Uso el material
		material->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(transform->GetTransform()));
	}
	Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, draw_vertices, true);
}

Square::Square() {
	float position_vertex_data[] = {
		 1.0f,  1.0f, 0.0f,  // top right
		 1.0f,  0.0f, 0.0f,  // bottom right
		 0.0f,  0.0f, 0.0f,  // bottom left
		 0.0f,  1.0f, 0.0f   // top left 
	};
	float color_vertex_data[] = {
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
	};
	unsigned int index_data[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	CreateVertexArrayID();
	CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0);
	CreateVertexData(color_vertex_data, sizeof(color_vertex_data), 4, Renderer::ARRAY_BUFFER, 1);
	CreateVertexData(index_data, sizeof(index_data), 2, Renderer::ELEMENT_BUFFER, -1);
	primitive = Renderer::TRIANGLES;
}

Square::~Square() {
}
