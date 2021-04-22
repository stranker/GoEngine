#include "Transform.h"

void Transform::_UpdateTransform() {
	transform = glm::mat4(1.0f);
	transform = matTrans * matRot * matScl;
}

void Transform::SetPosition(float x, float y, float z) {
	position.x = x;
	position.y = y;
	position.z = z;
	matTrans = glm::mat4(1.0f);
	matTrans = glm::translate(matTrans, glm::vec3(position.x, position.y, position.z));
	_UpdateTransform();
}

void Transform::SetPosition(Vector3 _position) {
	position = _position;
	matTrans = glm::mat4(1.0f);
	matTrans = glm::translate(matTrans, glm::vec3(position.x, position.y, position.z));
	_UpdateTransform();
}

void Transform::Translate(Vector3 _position){
	SetPosition(position + _position);
}

void Transform::SetScale(float x, float y, float z) {
	localScale.x = x;
	localScale.y = y;
	localScale.z = z;
	matScl = glm::mat4(1.0f);
	matScl = glm::scale(matScl, glm::vec3(localScale.x, localScale.y, localScale.z));
	_UpdateTransform();
}

void Transform::SetScale(Vector3 _scale) {
	localScale = _scale;
	matScl = glm::mat4(1.0f);
	matScl = glm::scale(transform, glm::vec3(localScale.x, localScale.y, localScale.z));
	_UpdateTransform();
}

void Transform::SetRotation(float angle, Vector3 axis) {
	rotation.x = angle * axis.x;
	rotation.y = angle * axis.y;
	rotation.z = angle * axis.z;
	matRot = glm::mat4(1.0f);
	matRot = glm::rotate(transform, glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));
	_UpdateTransform();
}

void Transform::RotateX(float angle) {
	rotation.x += angle;
	matRot = glm::rotate(transform, glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f));
	_UpdateTransform();
}

void Transform::RotateY(float angle) {
	rotation.y += angle;
	matRot = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
	_UpdateTransform();
}

void Transform::RotateZ(float angle) {
	rotation.z += angle;
	matRot = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	_UpdateTransform();
}


void Transform::LookAt(Vector3 _target) {
	LookAt(position, _target, Vector3().Up());
}

void Transform::LookAt(Vector3 _target, Vector3 _upVector) {
	LookAt(position, _target, _upVector);
}

void Transform::LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector) {
	position = _position;
	up = _upVector;
	transform = glm::mat4(1.0f);
	transform = glm::lookAt(glm::vec3(_position.x, _position.y, _position.z), glm::vec3(_target.x, _target.y, _target.z), glm::vec3(_upVector.x, _upVector.y, _upVector.z));
}

void Transform::SetEulerAngles(Vector3 _eulerAngles) {
	eulerAngles = _eulerAngles;
	foward.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	foward.y = sin(glm::radians(eulerAngles.x));
	foward.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	foward = foward.Normalize();
	right = foward.Cross(Vector3().Up());
	up = right.Cross(foward);
	LookAt(position, position + foward, up);
}

Vector3 Transform::GetFoward() const {
	return foward;
}

Vector3 Transform::GetRight() const {
	return right;
}

Vector3 Transform::GetPosition() const {
	return position;
}

Vector3 Transform::GetRotation() const {
	return rotation;
}

Vector3 Transform::GetScale() const {
	return localScale;
}

glm::mat4 Transform::GetTransform() {
	return transform;
}

Transform::Transform() {
	position = Vector3().Zero();
	rotation = Vector3().Zero();
	localScale = Vector3().One();
	right = Vector3().Right();
	up = Vector3().Up();
	foward = Vector3().Foward();
	transform = glm::mat4(1.0f);
	matTrans = glm::mat4(1.0f);
	matRot = glm::mat4(1.0f);
	matScl = glm::mat4(1.0f);
}


Transform::~Transform() {
}
