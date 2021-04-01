#include "Camera3D.h"

void Camera3D::Translate(Vector3 position){
    transform->Translate(position);
}

void Camera3D::Rotate(Vector3 rotation){
    RotateX(rotation.x);
    RotateY(rotation.y);
    RotateZ(rotation.z);
}

void Camera3D::RotateX(float _angle){
    transform->SetRotation(_angle, Vector3().Right());
}

void Camera3D::RotateY(float _angle){
    transform->SetRotation(_angle, Vector3().Up());
}

void Camera3D::RotateZ(float _angle){
    transform->SetRotation(_angle, Vector3().Foward());
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
    cout << "---------------------------" << endl;
    cout << "Camera3D: Update projection" << endl;
    cout << "fov: " << fov << endl;
    cout << "aspect: " << aspect << endl;
    cout << "near: " << near << endl;
    cout << "far: " << far << endl;
    cout << "---------------------------" << endl;
    //projection = glm::perspective(glm::radians(fov), aspect, near, far);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
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