#pragma once
#include "Camera.h"

class ENGINEDLL_API Camera3D : public Camera {
protected:
    float aspect;
    float fov = 45.0f;
    float near = 0.1f;
    float far = 1000.0f;
    Vector3 direction;
    Vector3 right;
    Vector3 up;
public:
    void Translate(Vector3 position);
    void Rotate(Vector3 rotation);
    void RotateX(float _angle);
    void RotateY(float _angle);
    void RotateZ(float _angle);
    void SetFov(float _fov);
    void SetNear(float _near);
    void SetFar(float _far);
    float GetFov() const;
    float GetNear() const;
    float GetFar() const;
    void SetAspect(float _width, float _height);
    void _UpdateProjection();
    Camera3D(float _width, float _height, float _fov, float _near, float _far);
    Camera3D(float _width, float _height);
	~Camera3D();
};

