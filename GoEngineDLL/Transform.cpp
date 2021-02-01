#include "Transform.h"

void Transform::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	UpdateModel();
}

void Transform::SetPosition(Vector3 _position) {
	position = _position;
	matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	UpdateModel();
}

void Transform::SetScale(float x, float y, float z) {
	localScale.x = x;
	localScale.y = y;
	localScale.z = z;
	matScale = glm::scale(glm::mat4(1.0f), glm::vec3(localScale.x , localScale.y , localScale.z));
	UpdateModel();
}

void Transform::SetScale(Vector3 _scale) {
	localScale = _scale;
	matScale = glm::scale(glm::mat4(1.0f), glm::vec3(localScale.x, localScale.y, localScale.z));
	UpdateModel();
}

void Transform::SetRotation(float angle, Vector3 axis) {
	rotation.x = angle * axis.x;
	rotation.y = angle * axis.y;
	rotation.z = angle * axis.z;
	matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));
	UpdateModel();
}

Vector3 Transform::GetPosition() {
	return position;
}

Vector3 Transform::GetRotation() {
	return rotation;
}

Vector3 Transform::GetScale() {
	return localScale;
}

glm::mat4 Transform::GetTransform() {
	return transform;
}

void Transform::UpdateModel() {
	transform = matTranslation * matRotation * matScale;
}

Transform::Transform() {
	position = Vector3().Zero();
	rotation = Vector3().Zero();
	localScale = Vector3().One();
	matTranslation = glm::mat4(1.0f);
	matRotation = glm::mat4(1.0f);
	matScale = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
}


Transform::~Transform() {
}
