#include "Primitive.h"

void Primitive::SetMaterial(SpatialMaterial _spatialMaterial) {
	spatialMaterial = _spatialMaterial;
}

void Primitive::Draw() {
	VisualInstance3D::Draw();
}
