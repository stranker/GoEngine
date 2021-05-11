#include "Entity2D.h"

void Entity2D::SetPosition(float x, float y) {
	transform->SetPosition(x, y, 0);
}

void Entity2D::SetPosition(Vector2 vec) {
	SetPosition(vec.x, vec.y);
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

Vector2 Entity2D::GetPosition() const{
	return Vector2(transform->GetPosition().x, transform->GetPosition().y);
}

float Entity2D::GetRotation() const{
	return rotationDegrees;
}

Vector2 Entity2D::GetScale() const{
	return Vector2(transform->GetScale().x, transform->GetScale().y);
}

void Entity2D::SetModulate(Color _new_modulate) {
	selfModulate = _new_modulate;
}

Color Entity2D::GetModulate() const {
	return selfModulate;
}

Transform * Entity2D::GetTransform() {
	return transform;
}

void Entity2D::Destroy() {
	Renderer::GetSingleton()->DestroyVertexData(vectorVertexData);
	if (transform) {
		delete transform;
	}
}

Entity2D::Entity2D(){
	selfModulate = Color();
}

Entity2D::~Entity2D(){
}
