#include "Transform.h"

void Transform::UpdateUnitVectors() {
	const glm::vec3 newFoward = normalize(glm::vec3(transform[2]));
	foward = Vector3(newFoward.x, newFoward.y, newFoward.z);
	right = foward.Cross(Vector3().Up()).Normalize();
	up = right.Cross(foward).Normalize();
}

void Transform::SetPosition(Vector3 _position) {
	position = _position;
	translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	UpdateTransform();
}

void Transform::Translate(Vector3 _position){
	position += _position;
	translateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
	UpdateTransform();
}

void Transform::SetScale(Vector3 _scale) {
	localScale = _scale;
	scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(localScale.x, localScale.y, localScale.z));
	UpdateTransform();
}

void Transform::SetRotation(float angle, Vector3 axis) {
	rotation.x = angle * axis.x;
	rotation.y = angle * axis.y;
	rotation.z = angle * axis.z;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(axis.x, axis.y, axis.z));
	UpdateUnitVectors();
	UpdateTransform();
}

void Transform::UpdateTransform() {
	transform = translateMatrix * rotateMatrix * scaleMatrix;
}

void Transform::RotateX(float angle) {
	rotation.x += angle;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
	UpdateUnitVectors();
	UpdateTransform();
}

void Transform::RotateY(float angle) {
	rotation.y += angle;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0, 1, 0));
	UpdateTransform();
	UpdateUnitVectors();
}

void Transform::RotateZ(float angle) {
	rotation.z += angle;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0, 0, 1));
	UpdateTransform();
	UpdateUnitVectors();
}

void Transform::SetEulerAngles(Vector3 _eulerAngles) {
	rotation.x = _eulerAngles.x;
	rotation.y = _eulerAngles.y;
	rotation.z = _eulerAngles.z;
	rotateMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0, 0.0, 0.0));
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotation.y), glm::vec3(0.0, 1.0, 0.0));
	rotateMatrix = glm::rotate(rotateMatrix, glm::radians(rotation.z), glm::vec3(0.0, 0.0, 1.0));
	UpdateTransform();
	UpdateUnitVectors();
}

void Transform::LookAt(Vector3 _target) {
	LookAt(position, position + _target, up);
}

void Transform::LookAt(Vector3 _target, Vector3 _upVector) {
	LookAt(position, position + _target, _upVector);
}

void Transform::LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector) {
	position = _position;
	up = _upVector;
	transform = glm::lookAt(glm::vec3(_position.x, _position.y, _position.z), glm::vec3(_target.x, _target.y, _target.z), glm::vec3(_upVector.x, _upVector.y, _upVector.z));
	UpdateUnitVectors();
}

void Transform::SetCanScale(bool value) {
	canScale = value;
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

Vector3 Transform::GetUp() const {
	return up;
}

Vector3 Transform::GetRotation() const {
	return rotation;
}

Vector3 Transform::GetScale() const {
	return localScale;
}

void Transform::operator*=(const Transform& otherTransform) {
	transform *= otherTransform.GetTransform();
}

Transform Transform::operator*(const Transform& otherTransform) const {
	Transform t = *this;
	t *= otherTransform;
	t.position += otherTransform.position;
	return t;
}

Vector3 Transform::operator*(const Vector3& vec) const {
	glm::vec4 vec4 = glm::vec4(vec.x, vec.y, vec.z, 1.0f);
	glm::vec4 newVec4 = transform * vec4;
	return Vector3(newVec4.x, newVec4.y, newVec4.z);
}

BoundingBox Transform::operator*(const BoundingBox& bbox) const {
	Transform t = *this;
	Vector3 min = t * bbox.min;
	Vector3 max = t * bbox.max;
	return BoundingBox(min, max);
}

glm::mat4 Transform::GetTransform() const{
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
	translateMatrix = glm::mat4(1.0f);
	rotateMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	UpdateTransform();
	UpdateUnitVectors();
}
