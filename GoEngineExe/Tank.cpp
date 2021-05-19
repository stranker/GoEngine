#include "Tank.h"

void Tank::Update(float deltaTime) {
	velocity = Vector3().Zero();
	rotationAngle = 0;
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)) { return; }
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity = model->GetTransform()->GetRight();
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity = model->GetTransform()->GetRight() * -1;
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		rotationAngle = -rotationSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		rotationAngle = rotationSpeed;
	}
	model->Translate(velocity * speed * deltaTime);
	model->Rotate(rotationAngle * deltaTime, Vector3().Up());
	spotlight->SetPosition(model->GetPosition() + spotlight->GetTransform()->GetFoward() * 2);
	spotlight->Rotate(rotationAngle * deltaTime, Vector3().Up());
	Vector3 cameraPos = model->GetPosition() + model->GetTransform()->GetRight() * cameraXOffset;
	cameraPos.y += cameraYOffset;
	Vector3 cameraTarget = model->GetPosition() + model->GetTransform()->GetRight() * aimDistance;
	camera->LookAt(cameraPos, cameraTarget, Vector3().Up());
}

Tank::Tank() {
	model = BaseGame::GetSingleton()->CreateMeshInstance("concept_tank/scene.gltf");
	model->SetScale(Vector3().One() * 0.01);
	model->Rotate(-90, Vector3().Up());
	spotlight = BaseGame::GetSingleton()->CreateSpotLight(Vector3(1, 0, 0), 1, 0.5, 10, Vector3().Foward(), Vector3(1, 0.09, 0.032), 12, 15);
	spotlight->Rotate(-180, Vector3().Up());
	camera = BaseGame::GetSingleton()->CreateCamera3D(800, 600);
}
