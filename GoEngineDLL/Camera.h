#pragma once
#include "Exports.h"
#include "Transform.h"

class ENGINEDLL_API Camera {
protected:
	Transform* transform; // view
	glm::mat4 projection;
	float width;
	float heigth;
public:
	glm::mat4 GetProjection();
	glm::mat4 GetMVPOf(glm::mat4 model);
	void SetSize(float _width, float _height);
	Vector2 GetSize() const;
	Camera(float _width, float _height);
	~Camera();
};

