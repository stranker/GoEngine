#pragma once
#include "BaseGame.h"

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.0f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.0f;

class GameCamera : public Camera3D{
private:
	Vector3 eulerAngles = Vector3().Zero();
	Vector2 lastMousePos = Vector2().Zero();

	Node3D* target;
	
	Vector3 position;
	Vector3 foward;
	Vector3 right;
	Vector3 up;

	static void OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void ProcessMousePosition();
	void UpdateCameraVectors();
public:
	void Update(float deltaTime) override;
	void SetTarget(Node3D* _target);
	GameCamera(float screenWidth, float screenHeight);
	~GameCamera() {};
};

