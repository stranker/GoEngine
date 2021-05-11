#include "VisualInstance3D.h"
#include "Line3D.h"

void VisualInstance3D::DrawGizmo() {
	gizmo->Draw();
}

void VisualInstance3D::UpdateGizmo() {
	gizmo->UpdateGizmo(transform);
}

void VisualInstance3D::SetPosition(Vector3 position) {
	Entity3D::SetPosition(position);
	UpdateGizmo();
}

void VisualInstance3D::Translate(Vector3 position) {
	Entity3D::Translate(position);
	UpdateGizmo();
}

void VisualInstance3D::Rotate(Vector3 rotation) {
	Entity3D::Rotate(rotation);
	UpdateGizmo();
}

void VisualInstance3D::Rotate(float angle, Vector3 axis) {
	Entity3D::Rotate(angle, axis);
	UpdateGizmo();
}

void VisualInstance3D::SetScale(Vector3 scale) {
	Entity3D::SetScale(scale);
	UpdateGizmo();
}

void VisualInstance3D::Destroy() {
	Entity3D::Destroy();
	if (gizmo){
		gizmo->Destroy();
		delete gizmo;
	}
}

VisualInstance3D::VisualInstance3D() {
	gizmo = new Gizmo3D();
}

VisualInstance3D::~VisualInstance3D() {
}
