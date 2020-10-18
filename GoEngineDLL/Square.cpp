#include "Square.h"


void Square::Draw() {
	if (material) {
		material->Use(); // Uso el material
		material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
	}

	renderer->BindVertexArray(vertexArrayID);

	renderer->BindBuffer(positionBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer posicion del tipo GL_ARRAY_BUFFER
	renderer->SetAttributePointer(0, 3); // Seteo los atributos del vertice de posicion

	renderer->BindBuffer(colorBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer posicion del tipo GL_ARRAY_BUFFER
	renderer->SetAttributePointer(1, 4); // Seteo los atributos del vertice de color

	renderer->BindBuffer(indexBuffer, Renderer::ELEMENT_BUFFER);

	renderer->DrawElements(primitive, 6);

	renderer->DisableBuffer(0); // Deshabilito el atributo (pos)
	renderer->DisableBuffer(1); // Deshabilito el atributo (color)
}

Square::Square(Renderer *_renderer) : Shape(_renderer) {
	float position_vertex_data[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
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
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 4);
	SetColorVertex(color_vertex_data,sizeof(color_vertex_data));
	SetIndex(index_data, sizeof(index_data));
	primitive = Renderer::TRIANGLES;
	SetScale(100, 100, 0);
}

Square::~Square() {
}
