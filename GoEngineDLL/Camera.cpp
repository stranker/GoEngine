#include "Camera.h"

void Camera::_UpdateProjection(float _fov, float aspect, float _near, float _far) {
    projection = glm::perspective(glm::radians(_fov), aspect, _near, _far);
}
