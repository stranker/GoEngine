#pragma once
#include "BaseGame.h"

class Tank {
private:
	Vector3 velocity;
	float speed = 10;
	float rotationAngle = 0;
	float rotationSpeed = 100;
	MeshInstance* model;
	SpotLight* spotlight;
	Camera3D* camera;
	const float cameraXOffset = -15;
	const float cameraYOffset = 12;
	const float aimDistance = 10;
public:
	void Update(float deltaTime);
	Tank();
};

