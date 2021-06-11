#include "Node2D.h"

void Node2D::SetPosition(Vector2 vec) {
	transform->SetPosition(Vector3(vec.x,vec.y,0));
}

void Node2D::Translate(Vector2 vec) {
	transform->Translate(Vector3(vec.x, vec.y, 0));
}

void Node2D::Rotate(float angle) {
	rotationDegrees = angle;
	transform->SetRotation(rotationDegrees, Vector3(0,0,1));
}

void Node2D::Scale(Vector2 vec) {
	transform->SetScale(Vector3(vec.x, vec.y, 1));
}

Vector2 Node2D::GetPosition() const{
	return Vector2(transform->GetPosition().x, transform->GetPosition().y);
}

float Node2D::GetRotation() const{
	return rotationDegrees;
}

Vector2 Node2D::GetScale() const{
	return Vector2(transform->GetScale().x, transform->GetScale().y);
}

void Node2D::SetModulate(Color _new_modulate) {
	selfModulate = _new_modulate;
}

Color Node2D::GetModulate() const {
	return selfModulate;
}

Transform * Node2D::GetTransform() {
	return transform;
}

Node2D::Node2D(){
	selfModulate = Color();
}