#pragma once
#include "BaseGame.h"

class Tank : public Node3D {
private:
	Vector3 velocity;
	float speed = 10;
	float rotationAngle = 0;
	float rotationSpeed = 100;
	float turretRotationAngle = 0;
	float turretRotationSpeed = 100;
	Node3D* model;
	Node3D* modelRoot;
	MeshInstance* turret;
	SpotLight* spotlight;
public:
	void Update(float deltaTime);
	Tank();
};

