#include "Tank.h"

void Tank::Update(float deltaTime) {
	velocity = Vector3().Zero();
	rotationAngle = 0;
	turretRotationAngle = 0;
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)) { return; }
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity = model->GetGlobalTransform()->GetFoward();
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity = model->GetGlobalTransform()->GetFoward() * -1;
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		rotationAngle = -rotationSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		rotationAngle = rotationSpeed;
	}
	model->Translate(velocity * speed * deltaTime);
	model->RotateY(rotationAngle * deltaTime);
	if (turret){
		if (Input::IsKeyPressed(Input::KEY_Q)) {
			turretRotationAngle += turretRotationSpeed;
		}
		if (Input::IsKeyPressed(Input::KEY_E)) {
			turretRotationAngle -= turretRotationSpeed;
		}
		//turret->Rotate(turretRotationAngle * deltaTime, Vector3().Up());
	}
}

Tank::Tank() {
	model = BaseGame::GetSingleton()->LoadModel("concept_tank/scene.gltf");
	model->SetScale(Vector3().One() * 0.01);
	modelRoot = (Node3D*)model->GetNode("RootNode (model correction matrix)");
	turret = (MeshInstance*)model->GetNode("Turret_01");
	modelRoot->Rotate(-90, Vector3().Up());
	turret->Rotate(50, Vector3().Up());
	//spotlight = BaseGame::GetSingleton()->CreateSpotLight(Vector3(1, 0, 0), 1, 0.5, 10, Vector3().Foward(), Vector3(1, 0.09, 0.032), 12, 15);
	//spotlight->Rotate(-180, Vector3().Up());
	AddChildren(model);
	//model->AddChildren(spotlight);
}
