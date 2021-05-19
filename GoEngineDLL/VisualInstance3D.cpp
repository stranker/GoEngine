#include "VisualInstance3D.h"
#include "Line3D.h"

void VisualInstance3D::DrawGizmo() {
	gizmo->Draw();
}

void VisualInstance3D::UpdateGizmo() {
	gizmo->UpdateGizmo(gizmo->GetTransform());
}

void VisualInstance3D::SetPosition(Vector3 position) {
	Entity3D::SetPosition(position);
	gizmo->SetPosition(position);
	UpdateGizmo();
}

void VisualInstance3D::Translate(Vector3 position) {
	Entity3D::Translate(position);
	gizmo->Translate(position);
	UpdateGizmo();
}

void VisualInstance3D::Rotate(Vector3 rotation) {
	Entity3D::Rotate(rotation);
	gizmo->Rotate(rotation);
	UpdateGizmo();
}

void VisualInstance3D::Rotate(float angle, Vector3 axis) {
	Entity3D::Rotate(angle, axis);
	gizmo->Rotate(angle, axis);
	UpdateGizmo();
}

void VisualInstance3D::SetScale(Vector3 scale) {
	Entity3D::SetScale(scale);
}

void VisualInstance3D::Destroy() {
	Entity3D::Destroy();
	if (gizmo){
		gizmo->Destroy();
		delete gizmo;
	}
}

void VisualInstance3D::Draw() {
	DrawGizmo();
}

VisualInstance3D::VisualInstance3D() {
	gizmo = new Gizmo3D();
}
