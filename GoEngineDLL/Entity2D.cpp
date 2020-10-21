#include "Entity2D.h"

void Entity2D::SetPosition(float x, float y) {
	transform->SetPosition(x, y, 0);
}

void Entity2D::SetPosition(Vector2 vec) {
}

void Entity2D::Translate(float x, float y) {
	transform->SetPosition(GetPosition().x + x, GetPosition().y + y, 0);
}

void Entity2D::Translate(Vector2 vec) {
	Translate(vec.x, vec.y);
}

void Entity2D::Rotate(float angle) {
	rotationDegrees = angle;
	transform->SetRotation(rotationDegrees, Vector3(0,0,1));
}

void Entity2D::Scale(float x, float y) {
	transform->SetScale(x, y, 0);
}

void Entity2D::Scale(Vector2 vec) {
	Scale(vec.x, vec.y);
}

Vector2 Entity2D::GetPosition() {
	return Vector2(transform->GetPosition().x, transform->GetPosition().y);
}

float Entity2D::GetRotation() {
	return rotationDegrees;
}

Vector2 Entity2D::GetScale() {
	return Vector2(transform->GetScale().x, transform->GetScale().y);
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
	selfModulate = Color();
}

Entity2D::~Entity2D(){
}
