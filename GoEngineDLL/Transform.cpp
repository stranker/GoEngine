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

void Transform::Translate(Vector3 _position){
	SetPosition(position + _position);
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
	matRotation = glm::rotate(matRotation, glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));
	UpdateModel();
}

void Transform::RotateX(float angle) {
	rotation.x = angle;
	matRotation = glm::rotate(matRotation, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	UpdateModel();
}

void Transform::RotateY(float angle) {
	rotation.y = angle;
	matRotation = glm::rotate(matRotation, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	UpdateModel();
}

void Transform::RotateZ(float angle) {
	rotation.z = angle;
	matRotation = glm::rotate(matRotation, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	UpdateModel();
}


void Transform::LookAt(Vector3 _target) {
	LookAt(position, _target, Vector3().Up());
}

void Transform::LookAt(Vector3 _target, Vector3 _upVector) {
	LookAt(position, _target, _upVector);
}

void Transform::LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector) {
	transform = glm::lookAt(glm::vec3(_position.x, _position.y, _position.z), glm::vec3(_target.x, _target.y, _target.z), glm::vec3(_upVector.x, _upVector.y, _upVector.z));
}

Vector3 Transform::Foward() {
	return Vector3();
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
	foward = Vector3().Foward();
	right = Vector3().Right();
	up = Vector3().Up();
	matTranslation = glm::mat4(1.0f);
	matRotation = glm::mat4(1.0f);
	matScale = glm::mat4(1.0f);
	transform = glm::mat4(1.0f);
}


Transform::~Transform() {
}
