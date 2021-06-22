#pragma once
#include "Utils.h"
#include "Transform.h"

class ENGINEDLL_API Camera {
protected:
    glm::mat4 projection = glm::mat4(1.0f);
    float width = 0;
    float heigth = 0;
public:
    virtual glm::mat4 GetView() const { return glm::mat4(1.0f); };
    virtual glm::mat4 GetProjection() const { return projection; };
    virtual glm::mat4 GetMVPOf(const Transform& _transform) const { return glm::mat4(1.0f); };
    virtual Transform GetTransform() const { return Transform(); };
    virtual Transform GetGlobalTransform() const { return Transform(); } ;
    void UpdateProjection(float _fov, float aspect, float _near, float _far);
    void SetSize(Vector2 size) {width = size.x; heigth = size.y;};
    Camera() { };
    Camera(float _width, float _heigth) {
        width = _width; 
        heigth = _heigth;
        projection = glm::mat4(1.0f);
    };
};

