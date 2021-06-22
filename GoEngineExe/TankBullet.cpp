#include "TankBullet.h"

void TankBullet::SetDirection(Vector3 dir) {
	direction = dir;
}

void TankBullet::Ready() {

}

void TankBullet::Update(float deltaTime) {
}


TankBullet::TankBullet() {
	model = ModelImporter::LoadModel("tank_shell/scene.gltf");
	model->SetScale(Vector3().One() * 0.5);
	AddChildren(model);
}
