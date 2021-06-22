#pragma once
#include "BaseGame.h"

class Tank : public Node3D {
private:
	float speed = 10;
	float rotationAngle = 0;
	float rotationSpeed = 100;
	float turretRotationAngle = 0;
	float turretRotationSpeed = 100;
	Node3D* model;
	Node3D* turret;
public:
	void Ready();
	void Update(float deltaTime);
	Tank();
};

