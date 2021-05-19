#pragma once
#include "BaseGame.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class GameCamera {
private:
	static Camera3D* camera;

	Vector3 position;
	Vector3 front;
	Vector3 up;
	Vector3 right;

	Vector3 eulerAngles;
	Vector2 lastMousePos;

	Entity3D* target;

	
	static void OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void _UpdateCameraVectors();
	void _ProcessMousePosition();
public:
	void SetPosition(Vector3 position);
	void Update(float deltaTime);
	void SetTarget(Entity3D* _target);
	GameCamera(float screenWidth, float screenHeight);
	~GameCamera() {};
};

