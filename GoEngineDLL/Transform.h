#pragma once
#include "Exports.h"
#include "Utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ENGINEDLL_API Transform {
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 localScale;

	Vector3 right;
	Vector3 up;
	Vector3 foward;

	glm::mat4 transform;

	glm::mat4 translateMatrix;
	glm::mat4 rotateMatrix;
	glm::mat4 scaleMatrix;

	bool canScale = true;

	void UpdateUnitVectors();
	void UpdateTransform();
public:
	void SetPosition(Vector3 _position);
	void Translate(Vector3 _position);
	void SetScale(Vector3 _scale);
	void SetRotation(float angle, Vector3 axis);
	void SetEulerAngles(Vector3 _eulerAngles);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void LookAt(Vector3 _target);
	void LookAt(Vector3 _target, Vector3 _upVector);
	void LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector);
	void SetCanScale(bool value);
	Vector3 GetFoward() const;
	Vector3 GetRight() const;
	Vector3 GetUp() const;
	Vector3 GetPosition() const;
	Vector3 GetRotation() const;
	Vector3 GetScale() const;
	glm::mat4 GetTransform() const;
	void operator*=(const Transform& otherTransform);
	Transform operator*(const Transform& otherTransform) const;
	Vector3 operator*(const Vector3& vec) const;
	BoundingBox operator*(const BoundingBox& bbox) const;
	Transform();
};

