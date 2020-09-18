#include "Transform.h"

void Transform::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	translation = glm::translate(glm::mat4(1.0f), position);
	UpdateModel();
}

void Transform::SetScale(float x, float y, float z) {
	localScale.x = x;
	localScale.y = y;
	localScale.z = z;
	scale = glm::scale(glm::mat4(1.0f), localScale);
	UpdateModel();
}

void Transform::SetRotation(float angle, glm::vec3 axis) {
	rotationDegrees.x = angle * axis.x;
	rotationDegrees.y = angle * axis.y;
	rotationDegrees.z = angle * axis.z;
	rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
	UpdateModel();
}

glm::vec3 Transform::GetPosition() {
	return position;
}

glm::vec3 Transform::GetRotation() {
	return rotationDegrees;
}

glm::vec3 Transform::GetScale() {
	return localScale;
}

glm::mat4 Transform::GetTransform() {
	return transform;
}

void Transform::UpdateModel() {
	transform = translation * rotation * scale;
}

Transform::Transform() {
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotationDegrees = glm::vec3(0.0f, 0.0f, 0.0f);
	localScale = glm::vec3(1.0f, 1.0f, 1.0f);
	translation = glm::mat4(1.0f);
	rotation = glm::mat4(1.0f);
	scale = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
}


Transform::~Transform() {
}
