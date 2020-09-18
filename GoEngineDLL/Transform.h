#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform {
protected:
	glm::vec3 position;
	glm::vec3 rotationDegrees;
	glm::vec3 localScale;

	glm::mat4 translation;
	glm::mat4 rotation;
	glm::mat4 scale;

	glm::mat4 transform;

public:
	void SetPosition(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void SetRotation(float angle, glm::vec3 axis);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
	void UpdateModel();
	Transform();
	~Transform();
};

