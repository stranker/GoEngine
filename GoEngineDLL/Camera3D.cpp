#include "Camera3D.h"

void Camera3D::CalculateDirection() {
    direction.x = cos(glm::radians(transform->GetRotation().y)) * cos(glm::radians(transform->GetRotation().x));
    direction.y = sin(glm::radians(transform->GetRotation().x));
    direction.z = sin(glm::radians(transform->GetRotation().y)) * cos(glm::radians(transform->GetRotation().x));
}

void Camera3D::SetPosition(Vector3 position) {
    transform->SetPosition(position);
}

void Camera3D::Translate(Vector3 position){
    transform->Translate(position);
}

void Camera3D::Rotate(float angle, Vector3 axis) {
    transform->SetRotation(angle, axis);
}

void Camera3D::Rotate(Vector3 rotation){
    RotateX(rotation.x);
    RotateY(rotation.y);
    RotateZ(rotation.z);
}

void Camera3D::RotateX(float _angle){
    transform->RotateX(_angle);
    CalculateDirection();
}

void Camera3D::RotateY(float _angle){
    transform->RotateY(_angle);
    CalculateDirection();
}

void Camera3D::RotateZ(float _angle){
    transform->RotateZ(_angle);
    CalculateDirection();
}

void Camera3D::SetFov(float _fov){
    fov = _fov;
    _UpdateProjection();
}

void Camera3D::SetNear(float _near){
    near = _near;
    _UpdateProjection();
}

void Camera3D::SetFar(float _far){
    far = _far;
    _UpdateProjection();
}

Vector3 Camera3D::GetFoward() const {
    return transform->GetFoward();
}

Vector3 Camera3D::GetDirection() const {
    return direction;
}

Vector3 Camera3D::GetRight() const {
    return transform->GetRight();
}

float Camera3D::GetFov() const {
    return fov;
}

float Camera3D::GetNear() const {
    return near;
}

float Camera3D::GetFar() const {
    return far;
}

void Camera3D::SetAspect(float _width, float _height){
    aspect = _width / _height;
    _UpdateProjection();
}

void Camera3D::_UpdateProjection(){
    projection = glm::perspective(glm::radians(fov), aspect, near, far);
}

Camera3D::Camera3D(float _width, float _height, float _fov, float _near, float _far) : Camera(_width, _height){
    name = "Camera3D";
    aspect = _width / _height;
    fov = _fov;
    near = _near;
    far = _far;
    _UpdateProjection();
}

Camera3D::Camera3D(float _width, float _height) : Camera(_width, _height) {
    name = "Camera3D";
    aspect = _width / _height;
    cout << "Camera3D: Creating Camera3D" << endl;
    _UpdateProjection();
}


Camera3D::~Camera3D(){
}