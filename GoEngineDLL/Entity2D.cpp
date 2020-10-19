#include "Entity2D.h"

void Entity2D::SetPosition(float x, float y, float z) {
	transform->SetPosition(x, y, z);
}

void Entity2D::SetRotation(float angle, glm::vec3 axis) {
	transform->SetRotation(angle, axis);
}

void Entity2D::SetScale(float x, float y, float z) {
	transform->SetScale(x, y, z);
}

glm::vec3 Entity2D::GetPosition() {
	return transform->GetPosition();
}

glm::vec3 Entity2D::GetRotation() {
	return transform->GetRotation();
}

glm::vec3 Entity2D::GetScale() {
	return transform->GetScale();
}

void Entity2D::SetMaterial(Material *_material) {
	material = _material;
	material->LoadShaders("SimpleVertexShader.shader", "SimpleFragmentShader.shader");
}

void Entity2D::CreateVertexArrayID() {
	glGenVertexArrays(1, (&vertexArrayID));
	glBindVertexArray(vertexArrayID);
}

void Entity2D::SetPositionVertex(float *_vertex, size_t dataSize, size_t vertexCount) {
	positionVertex = _vertex;
	positionVertexCount = vertexCount;
	positionBuffer = renderer->CreateVertexBuffer(positionVertex, dataSize, Renderer::ARRAY_BUFFER);
}

void Entity2D::SetIndex(unsigned int *_index, size_t indexSize) {
	index = _index;
	indexBuffer = renderer->CreateVertexBuffer(index, indexSize, Renderer::ELEMENT_BUFFER);
}

void Entity2D::SetColorVertex(float * _colorVertex, size_t dataSize) {
	colorVertex = _colorVertex;
	colorBuffer = renderer->CreateVertexBuffer(colorVertex, dataSize, Renderer::ARRAY_BUFFER);
}

void Entity2D::Destroy() {
	if (renderer) {
		renderer->DeleteBuffer(positionBuffer);
		renderer->DeleteBuffer(colorBuffer);
	}
	if (material) {
		material = NULL;
	}
	if (transform) {
		delete transform;
	}
}

Entity2D::Entity2D(Renderer* _renderer) : Entity(_renderer){
	selfModulate = Color(1, 1, 1, 1);
}

Entity2D::~Entity2D(){
}
