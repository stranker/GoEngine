#include "Tank.h"

void Tank::Ready() {
}

void Tank::Update(float deltaTime) {
	Vector3 velocity = Vector3();
	if (Input::IsMouseButtonPressed(Input::MOUSE_BUTTON_2)) { return; }
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity = GetTransform()->GetFoward() * -speed;
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity = GetTransform()->GetFoward() * speed;
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		RotateY(rotationSpeed * -deltaTime);
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		RotateY(rotationSpeed * deltaTime);
	}
	Translate(velocity * deltaTime);
	if (turret){
		if (Input::IsKeyPressed(Input::KEY_Q)) {
			turret->RotateY(turretRotationSpeed * deltaTime);
		}
		if (Input::IsKeyPressed(Input::KEY_E)) {
			turret->RotateY(turretRotationSpeed * -deltaTime);
		}
	}
}

Tank::Tank() {
	name = "TankNode";
	//model = ResourceManager::LoadModel("concept_tank/scene.gltf", "Tank");
	model = ResourceManager::LoadModel("escorpion/tank.gltf", "Tank");
	AddChildren(model);
	//model->SetScale(Vector3().One() * 0.01);
	//model->RotateY(-90);
	turret = (Node3D*)model->GetNode("Torreta");
}
