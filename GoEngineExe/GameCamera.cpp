#include "GameCamera.h"

Camera3D* GameCamera::camera = NULL;


void GameCamera::OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	float fov = camera->GetFov() - (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
	camera->SetFov(fov);
}

void GameCamera::_ProcessMousePosition() {
	Vector2 mousePos = Input::GetMousePosition();
	Vector2 offset = Vector2(mousePos.x - lastMousePos.x, lastMousePos.y - mousePos.y);
	lastMousePos = mousePos;
	offset = offset.Normalize() * 0.5f;
	eulerAngles.y += offset.x;
	eulerAngles.x += offset.y;
	eulerAngles.x = Utils::Clamp(eulerAngles.x, -89.0f, 89.0f);

	_UpdateCameraVectors();
}

void GameCamera::SetPosition(Vector3 _position) {
	camera->SetPosition(position);
}

void GameCamera::Update(float deltaTime) {
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)){
		Vector3 velocity = Vector3().Zero();
		if (Input::IsKeyPressed(Input::KEY_W)) {
			velocity += front;
		}
		if (Input::IsKeyPressed(Input::KEY_S)) {
			velocity += front * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_A)) {
			velocity += right * -1;
		}
		if (Input::IsKeyPressed(Input::KEY_D)) {
			velocity += right;
		}
		position += velocity.Normalize() * SPEED * deltaTime;
		_ProcessMousePosition();
	}
}

void GameCamera::SetTarget(Entity3D* _target) {
	target = _target;
}

void GameCamera::_UpdateCameraVectors() {
	Vector3 newFront;
	newFront.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	newFront.y = sin(glm::radians(eulerAngles.x));
	newFront.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	front = newFront.Normalize();
	// also re-calculate the Right and Up vector
	right = front.Cross(Vector3().Up()).Normalize();// normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = right.Cross(front).Normalize();
	camera->LookAt(position, position + front, up);
}

GameCamera::GameCamera(float screenWidth, float screenHeight) {
	camera = BaseGame::GetSingleton()->CreateCamera3D(screenWidth, screenHeight);
	camera->SetFov(FOV);
	lastMousePos = Vector2(screenWidth, screenHeight) * 0.5f;
	Input::SetMouseScrollCallback(OnMouseScrollCallback);
	eulerAngles = Vector3(0, YAW, 0);
	position = Vector3().Zero();
	front = Vector3().Zero();
	up = Vector3().Zero();
	right = Vector3().Zero();
	_UpdateCameraVectors();
}