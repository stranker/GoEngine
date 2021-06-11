#include "Primitive.h"

void Primitive::SetMaterial(SpatialMaterial* _spatialMaterial) {
	spatialMaterial = _spatialMaterial;
}

void Primitive::Draw() {
	Node3D::Draw();
}
