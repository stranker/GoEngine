#pragma once

#include "Exports.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ENGINEDLL_API Transform {
protected:
	Vector3 position;
	Vector3 rotation;
	Vector3 localScale;

	Vector3 foward;
	Vector3 right;
	Vector3 up;

	glm::mat4 matTranslation;
	glm::mat4 matRotation;
	glm::mat4 matScale;

	glm::mat4 transform;
public:
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector3 _position);
	void Translate(Vector3 _position);
	void SetScale(float x, float y, float z);
	void SetScale(Vector3 _scale);
	void SetRotation(float angle, Vector3 axis);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void LookAt(Vector3 _target);
	void LookAt(Vector3 _target, Vector3 _upVector);
	void LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector);
	Vector3 Foward();
	Vector3 GetPosition();
	Vector3 GetRotation();
	Vector3 GetScale();
	glm::mat4 GetTransform();
	void UpdateModel();
	Transform();
	~Transform();
};

