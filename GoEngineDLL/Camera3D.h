#pragma once
#include "Node3D.h"
#include "Camera.h"
#include "CameraFrustum.h"

class ENGINEDLL_API Camera3D : public Camera, public Node3D {
protected:
    float aspect;
    float fov = 45.0f;
    float near = 0.1f;
    float far = 1000.0f;
    CameraFrustum frustum;
    void UpdateProjection();
    virtual void OnTransformUpdate() override;
public:
    glm::mat4 GetView() const override;
    glm::mat4 GetProjection() const override;
    glm::mat4 GetMVPOf(const Transform& _transform) const override;
    void SetFov(float _fov);
    void SetNear(float _near);
    void SetFar(float _far);
    float GetFov() const;
    float GetNear() const;
    float GetFar() const;
    Vector3 GetFoward() const;
    Vector3 GetRight() const;
    Vector3 GetUp() const;
    void SetAspect(float _width, float _height);
    bool IsPointInFrustum(const Vector3& pos);
    bool IsBoxVisible(const Transform& transform, const BoundingBox& bbox);
    bool IsBoxVisible(const BoundingBox& bbox);
    Camera3D(float _width, float _height, float _fov, float _near, float _far);
    Camera3D(float _width, float _height);
};

