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

void GameCamera::SetPosition(Vector3 position) {
	camera->SetPosition(position);
}

void GameCamera::Update(float deltaTime) {
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)){
		if (Input::IsKeyPressed(Input::KEY_W)) {
			camera->Translate(cameraFront * SPEED * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_S)) {
			camera->Translate(cameraFront * -SPEED * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_A)) {
			camera->Translate(cameraRight * -SPEED * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_D)) {
			camera->Translate(cameraRight * SPEED * deltaTime);
		}
		_ProcessMousePosition();
	}
}

void GameCamera::_UpdateCameraVectors() {
	Vector3 front;
	front.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	front.y = sin(glm::radians(eulerAngles.x));
	front.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	cameraFront = front.Normalize();
	cameraRight = cameraFront.Cross(Vector3().Up());
	cameraUp = cameraRight.Cross(cameraFront);
	camera->LookAt(camera->GetPosition(), camera->GetPosition() + cameraFront, cameraUp);
}

GameCamera::GameCamera(float screenWidth, float screenHeight) {
	camera = BaseGame::GetSingleton()->CreateCamera3D(screenWidth, screenHeight);
	camera->SetFov(FOV);
	lastMousePos = Vector2(screenWidth, screenHeight) * 0.5f;
	Input::SetMouseScrollCallback(OnMouseScrollCallback);
	eulerAngles = Vector3(0, YAW, 0);
	cameraFront = Vector3().Foward();
	cameraRight = Vector3().Right();
	_UpdateCameraVectors();
}

GameCamera::~GameCamera() {
}
