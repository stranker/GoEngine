#include "GameCamera.h"

Camera3D* GameCamera::camera = NULL;
Vector3 GameCamera::eulerAngles = Vector3();
Vector3 GameCamera::cameraFront = Vector3();
Vector2 GameCamera::lastMousePos = Vector2();


void GameCamera::OnMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	float fov = camera->GetFov() - (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
	camera->SetFov(fov);
}

void GameCamera::OnMousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
	Vector2 mousePos = Vector2(xpos, ypos);
	Vector2 offset = Vector2(mousePos.x - lastMousePos.x, lastMousePos.y - mousePos.y);
	lastMousePos = mousePos;

	const float sensitivity = 0.1f;
	offset = offset * sensitivity;

	eulerAngles.y = offset.x;
	eulerAngles.x = offset.y;

	eulerAngles.x = Utils::Clamp(eulerAngles.x, -89.0f, 89.0f);

	Vector3 direction;
	direction.x = cos(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	direction.y = sin(glm::radians(eulerAngles.x));
	direction.z = sin(glm::radians(eulerAngles.y)) * cos(glm::radians(eulerAngles.x));
	cameraFront = direction.Normalize();
}

void GameCamera::Update(float deltaTime) {
	if (Input::IsKeyPressed(Input::KEY_W)) {
		camera->Translate(Vector3().Up() * -cameraVelocity * deltaTime);
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		camera->Translate(Vector3().Down() * -cameraVelocity * deltaTime);
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		camera->Translate(Vector3().Right() * cameraVelocity * deltaTime);
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		camera->Translate(Vector3().Right() * -cameraVelocity * deltaTime);
	}
	if (Input::IsKeyPressed(Input::KEY_1)) {
		camera->Translate(Vector3().Foward() * -cameraVelocity * deltaTime);
	}
	if (Input::IsKeyPressed(Input::KEY_2)) {
		camera->Translate(Vector3().Foward() * cameraVelocity * deltaTime);
	}
	camera->LookAt(camera->GetPosition() + cameraFront);
}

void GameCamera::Destroy() {
	if (camera)	{
		camera->Destroy();
		delete camera;
	}
}

void GameCamera::LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector) {
	cameraTarget = _target;
	cameraDirection = (_position - cameraTarget).Normalize();
	cameraRight = (Vector3().Up().Cross(cameraDirection)).Normalize();
	cameraUp = cameraDirection.Cross(cameraRight);
	camera->LookAt(_position, _target, _upVector);
}

GameCamera::GameCamera(float screenWidth, float screenHeight) {
	camera = BaseGame::GetSingleton()->CreateCamera3D(screenWidth, screenHeight);
	lastMousePos = Vector2(screenWidth, screenHeight) * 0.5f;
	Input::SetMouseScrollCallback(OnMouseScrollCallback);
	Input::SetMousePositionCallback(OnMousePositionCallback);
}

GameCamera::~GameCamera() {
}
