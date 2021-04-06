#pragma once
#include "BaseGame.h"

class GameCamera {
private:
	static Camera3D* camera;
	const float cameraVelocity = 10;
	Vector3 cameraTarget;
	Vector3 cameraDirection;
	Vector3 cameraRight;
	Vector3 cameraUp;
	static Vector3 eulerAngles;

	static Vector2 lastMousePos;

	static Vector3 cameraFront;

	static void OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static void OnMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
public:
	void Update(float deltaTime);
	void Destroy();
	void LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector);
	GameCamera(float screenWidth, float screenHeight);
	~GameCamera();
};

