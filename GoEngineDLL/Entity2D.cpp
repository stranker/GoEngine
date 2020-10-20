#include "Entity2D.h"

void Entity2D::SetPosition(float x, float y) {
	transform->SetPosition(x, y, 0);
}

void Entity2D::Translate(float x, float y) {
	transform->SetPosition(GetPosition().x + x, GetPosition().y + y, 0);
}

void Entity2D::Rotate(float angle) {
	rotationDegrees = angle;
	transform->SetRotation(rotationDegrees, glm::vec3(0,0,1));
}

void Entity2D::Scale(float x, float y) {
	transform->SetScale(x, y, 0);
}

glm::vec2 Entity2D::GetPosition() {
	return transform->GetPosition();
}

float Entity2D::GetRotation() {
	return rotationDegrees;
}

glm::vec2 Entity2D::GetScale() {
	return transform->GetScale();
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

void Entity2D::SetModulate(Color _new_modulate) {
	selfModulate = _new_modulate;
}

void Entity2D::Destroy() {
	if (renderer) {
		renderer->DeleteBuffer(positionBuffer);
		renderer->DeleteBuffer(colorBuffer);
	}
	if (transform) {
		delete transform;
	}
}

Entity2D::Entity2D(Renderer* _renderer) : Entity(_renderer){
	selfModulate = Color(1, 1, 1);
}

Entity2D::~Entity2D(){
}
