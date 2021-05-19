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

	Vector3 right;
	Vector3 up;
	Vector3 foward;

	glm::mat4 transform;
	glm::mat4 matTrans;
	glm::mat4 matRot;
	glm::mat4 matScl;

	bool canScale = true;

	void _UpdateTransform();
	void _UpdateUnitVectors();
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
	void SetCanScale(bool value);
	Vector3 GetFoward() const;
	Vector3 GetRight() const;
	Vector3 GetPosition() const;
	Vector3 GetRotation() const;
	Vector3 GetScale() const;
	glm::mat4 GetTransform();
	Transform();
	~Transform();
};

