#include "Tank.h"

void Tank::Update(float deltaTime) {
	velocity = Vector3().Zero();
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)) { return; }
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity = model->GetTransform()->GetRight();
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity = model->GetTransform()->GetRight() * -1;
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		rotationAngle -= deltaTime * rotationSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		rotationAngle += deltaTime * rotationSpeed;
	}
	model->Translate(velocity * speed * deltaTime);
	model->RotateY(rotationAngle);
}

Tank::Tank() {
	model = BaseGame::GetSingleton()->CreateMeshInstance("concept_tank/scene.gltf");
	model->SetScale(Vector3().One() * 0.01);
	model->Rotate(-90, Vector3().Up());
}
