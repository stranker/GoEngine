#pragma once
#include "Exports.h"
#include "Transform.h"

class ENGINEDLL_API Camera {
protected:
	Transform* transform; // view
	glm::mat4 projection;
	float width;
	float heigth;
	glm::mat4 _testView = glm::mat4(1.0f);
public:
	string name;
	glm::mat4 GetProjection();
	glm::mat4 GetMVPOf(glm::mat4 model);
	void SetSize(float _width, float _height);
	Vector2 GetSize() const;
	void Destroy();
	void LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector);
	void LookAt(Vector3 _target, Vector3 _upVector);
	void LookAt(Vector3 _target);
	Camera(float _width, float _height);
	~Camera();
};

