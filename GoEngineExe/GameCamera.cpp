#include "GameCamera.h"

void GameCamera::OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
}

void GameCamera::ProcessMousePosition() {
	Vector2 mousePos = Input::GetMousePosition();
	Vector2 offset = Vector2(mousePos.x - lastMousePos.x, lastMousePos.y - mousePos.y);
	lastMousePos = mousePos;
	offset = offset.Normalize() * 0.5f;
	eulerAngles.y += offset.x;
	eulerAngles.x += offset.y;
	eulerAngles.x = Utils::Clamp(eulerAngles.x, -89.0f, 89.0f);
	UpdateCameraVectors();
}

void GameCamera::UpdateCameraVectors() {
	Vector3 newFoward;
	newFoward.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	newFoward.y = sin(glm::radians(eulerAngles.x));
	newFoward.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	foward = newFoward.Normalize();
	// also re-calculate the Right and Up vector
	right = foward.Cross(Vector3().Up()).Normalize();// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = right.Cross(foward).Normalize();
}

void GameCamera::Update(float deltaTime) {
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)){
		Vector3 velocity = Vector3().Zero();
		if (Input::IsKeyPressed(Input::KEY_W)) {
			velocity += foward;
		}
		if (Input::IsKeyPressed(Input::KEY_S)) {
			velocity += foward * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_A)) {
			velocity += right * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_D)) {
			velocity += right;
		}
		Translate(velocity.Normalize() * SPEED * deltaTime);
		LookAt(GetPosition(), GetPosition() + foward, up);
		ProcessMousePosition();
	}
}

void GameCamera::SetTarget(Node3D* _target) {
	target = _target;
}

GameCamera::GameCamera(float screenWidth, float screenHeight) : Camera3D(screenWidth, screenHeight) {
	className = "GameCamera";
	lastMousePos = Vector2(screenWidth, screenHeight) * 0.5f;
	Input::SetMouseScrollCallback(OnMouseScrollCallback);
	eulerAngles = Vector3().Zero();
	uiLocked = true;
}