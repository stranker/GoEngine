#include "Camera3D.h"

glm::mat4 Camera3D::GetView() const{
    return transform->GetTransform();
}

glm::mat4 Camera3D::GetProjection() const {
    return projection;
}

glm::mat4 Camera3D::GetMVPOf(const Transform& _transform) const{
    return projection * transform->GetTransform() * _transform.GetTransform();
}

void Camera3D::SetFov(float _fov){
    fov = _fov;
    UpdateProjection();
}

void Camera3D::SetNear(float _near){
    near = _near;
    UpdateProjection();
}

void Camera3D::SetFar(float _far){
    far = _far;
    UpdateProjection();
}

Vector3 Camera3D::GetFoward() const {
    return transform->GetFoward();
}

Vector3 Camera3D::GetRight() const {
    return transform->GetRight();
}

Vector3 Camera3D::GetUp() const {
    return transform->GetUp();
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
    UpdateProjection();
}

void Camera3D::UpdateProjection(){
    _UpdateProjection(fov, aspect, near, far);
    frustum.CalculateFrustum(this);
}

void Camera3D::OnTransformUpdate() {
    frustum.CalculateFrustum(this);
}

bool Camera3D::IsPointInFrustum(const Vector3& pos) {
    return frustum.IsPointInside(pos);
}

bool Camera3D::IsBoxVisible(const Transform& transform, const BoundingBox& bbox) {
    return frustum.IsBBoxInside(transform, bbox);
}

bool Camera3D::IsBoxVisible(const BoundingBox& bbox) {
    return frustum.IsBBoxInside(bbox);
}

void Camera3D::Draw() {
    frustum.Draw(globalTransform);
}

Camera3D::Camera3D(float _width, float _height, float _fov, float _near, float _far) : Camera3D(_width, _height){
    fov = _fov;
    near = _near;
    far = _far;
}

Camera3D::Camera3D(float _width, float _height) : Camera(_width, _height) {
    SetDefaultName("Camera3D");
    aspect = _width / _height;
    Renderer::GetSingleton()->SetCurrentCamera(this);
    UpdateProjection();
    frustum.CalculateFrustum(this);
    is3DNode = false;
}