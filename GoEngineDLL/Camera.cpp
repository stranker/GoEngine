#include "Camera.h"

glm::mat4 Camera::GetProjection() {
	return projection;
}

glm::mat4 Camera::GetView() {
	return transform->GetTransform();
}

glm::mat4 Camera::GetMVPOf(glm::mat4 model) {
	return projection * transform->GetTransform() * model;
}

void Camera::SetSize(float _width, float _height) {
	projection = glm::ortho(0.0f, _width, _height, 0.0f, -0.1f, 100.0f); // camara ortogonal con ancho alto near y el far
}

Vector2 Camera::GetSize() const {
	return Vector2(width, heigth);
}

void Camera::Destroy() {
	if (transform != NULL){
		delete transform;
		transform = NULL;
	}
}

void Camera::LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector) {
	transform->LookAt(_position, _target, _upVector);
}

void Camera::LookAt(Vector3 _target, Vector3 _upVector) {
	LookAt(transform->GetPosition(), _target, _upVector);
}

void Camera::LookAt(Vector3 _target) {
	LookAt(_target, Vector3().Up());
}

Vector3 Camera::GetFoward() const {
	return transform->GetFoward();
}

Vector3 Camera::GetRight() const {
	return transform->GetRight();
}

Vector3 Camera::GetPosition() const {
	return transform->GetPosition();
}

Transform* Camera::GetTransform() const {
	return transform;
}

Camera::Camera(float _width, float _height) {
	name = "Camera";
	transform = new Transform();
	SetSize(_width, _height);
}


Camera::~Camera() {
}