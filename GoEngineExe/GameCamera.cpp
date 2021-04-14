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

	_UpdateCamera();
}

void GameCamera::SetPosition(Vector3 position) {
	camera->SetPosition(position);
}

void GameCamera::Update(float deltaTime) {
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)){
		if (Input::IsKeyPressed(Input::KEY_W)) {
			camera->Translate(camera->GetFoward() * SPEED * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_S)) {
			camera->Translate(camera->GetFoward() * -SPEED * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_A)) {
			camera->Translate(camera->GetRight() * -SPEED * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_D)) {
			camera->Translate(camera->GetRight() * SPEED * deltaTime);
		}
		_ProcessMousePosition();
	}
}

void GameCamera::_UpdateCamera() {
	camera->SetEulerAngles(eulerAngles);
}

GameCamera::GameCamera(float screenWidth, float screenHeight) {
	camera = BaseGame::GetSingleton()->CreateCamera3D(screenWidth, screenHeight);
	camera->SetFov(FOV);
	lastMousePos = Vector2(screenWidth, screenHeight) * 0.5f;
	Input::SetMouseScrollCallback(OnMouseScrollCallback);
	eulerAngles = Vector3(0, YAW, 0);
	_UpdateCamera();
}

GameCamera::~GameCamera() {
}
