#include "Primitive.h"

void Primitive::DrawGizmo() {
	gizmo->Draw();
}

void Primitive::SetMaterial(SpatialMaterial* _spatialMaterial) {
	spatialMaterial = _spatialMaterial;
}

void Primitive::SetPosition(Vector3 position) {
	Entity3D::SetPosition(position);
	gizmo->SetPosition(position);
}

void Primitive::Translate(Vector3 position) {
	Entity3D::Translate(position);
	gizmo->Translate(position);
}

void Primitive::Rotate(Vector3 rotation) {
	Entity3D::Rotate(rotation);
	gizmo->Rotate(rotation);
}

void Primitive::Rotate(float angle, Vector3 axis) {
	Entity3D::Rotate(angle, axis);
	gizmo->Rotate(angle, axis);
}

void Primitive::SetScale(Vector3 scale) {
	Entity3D::SetScale(scale);
	gizmo->SetScale(scale);
}

Primitive::Primitive(){
	gizmo = new Gizmo();
}

Primitive::~Primitive() {
	if (gizmo){
		gizmo->Destroy();
		delete gizmo;
	}
	if (spatialMaterial){
		spatialMaterial->Destroy();
		delete spatialMaterial;
	}
}
