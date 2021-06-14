#include "Tank.h"

void Tank::Ready() {
	model = ModelImporter::LoadModel("concept_tank/scene.gltf");
	AddChildren(model);
	model->SetScale(Vector3().One() * 0.01);
	turret = (Node3D*)model->GetNode("MeshInstance241");
	PrintTree();
	//Rotate(-90, Vector3().Up());
	PRINT_DEBUG(GetTransform()->GetFoward().ToString());
	model->Rotate(180, Vector3().Up());
	//turret->Rotate(50, Vector3().Up());
}

void Tank::Update(float deltaTime) {
	velocity = Vector3().Zero();
	rotationAngle = 0;
	turretRotationAngle = 0;
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)) { return; }
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity = GetTransform()->GetFoward();
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity = GetTransform()->GetFoward() * -1;
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		rotationAngle = -rotationSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		rotationAngle = rotationSpeed;
	}
	Translate(velocity * speed * deltaTime);
	if (rotationAngle > 0 || rotationAngle < 0){
		RotateY(rotationAngle * deltaTime);
		PRINT_DEBUG(GetTransform()->GetFoward().ToString());
	}
	if (turret){
		if (Input::IsKeyPressed(Input::KEY_Q)) {
			turretRotationAngle += turretRotationSpeed;
		}
		if (Input::IsKeyPressed(Input::KEY_E)) {
			turretRotationAngle -= turretRotationSpeed;
		}
		turret->RotateY(turretRotationAngle * deltaTime);
	}
}