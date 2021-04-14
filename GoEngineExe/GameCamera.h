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

	Vector3 eulerAngles;
	Vector2 lastMousePos;

	static void OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void _UpdateCamera();
	void _ProcessMousePosition();
public:
	void SetPosition(Vector3 position);
	void Update(float deltaTime);
	GameCamera(float screenWidth, float screenHeight);
	~GameCamera();
};

