#include "Primitive.h"

void Primitive::SetMaterial(SpatialMaterial* _spatialMaterial) {
	spatialMaterial = _spatialMaterial;
}

void Primitive::Destroy() {
	if (spatialMaterial) {
		spatialMaterial->Destroy();
		delete spatialMaterial;
	}
}

Primitive::Primitive(){
}

Primitive::~Primitive() {
}
