#include "Primitive.h"

void Primitive::SetMaterial(SpatialMaterial* _spatialMaterial) {
	spatialMaterial = _spatialMaterial;
}

void Primitive::Draw() {
	Node3D::Draw();
}

Primitive::Primitive() {
	defaultMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/SpatialMaterial.fs", "defaultMaterial");
	defaultMaterial->CreateMaterial(0.5f, 0.0f, "white_texture.png", "white_texture.png");
	spatialMaterial = defaultMaterial;
}
