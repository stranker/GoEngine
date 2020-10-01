#include "Camera.h"

glm::mat4 Camera::GetProjection() {
	return projection;
}

glm::mat4 Camera::GetMVPOf(glm::mat4 model) {
	return projection * transform->GetTransform() * model;
}

void Camera::SetSize(float _width, float _height) {
	projection = glm::ortho(0.0f, _width, 0.0f, _height, 0.0f, 100.0f); // camara ortogonal con ancho alto near y el far
}

Camera::Camera(float _width, float _height) {
	transform = new Transform();
	SetSize(_width, _height);
}


Camera::~Camera() {
}