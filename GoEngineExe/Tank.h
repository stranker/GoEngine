#pragma once
#include "BaseGame.h"

class Tank {
private:
	Vector3 velocity;
	float speed = 10;
	float rotationAngle = 0;
	float rotationSpeed = 100;
	MeshInstance* model;
public:
	void Update(float deltaTime);
	Tank();
};

