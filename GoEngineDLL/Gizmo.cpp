#include "Gizmo.h"

void Gizmo::SetPosition(Vector3 position) {
	redLine->SetPosition(position);
	blueLine->SetPosition(position);
	greenLine->SetPosition(position);
}

void Gizmo::Translate(Vector3 position) {
	redLine->Translate(position);
	blueLine->Translate(position);
	greenLine->Translate(position);
}

void Gizmo::Rotate(Vector3 rotation) {
	redLine->Rotate(rotation);
	blueLine->Rotate(rotation);
	greenLine->Rotate(rotation);
}

void Gizmo::Rotate(float angle, Vector3 axis) {
	redLine->Rotate(angle, axis);
	blueLine->Rotate(angle, axis);
	greenLine->Rotate(angle, axis);
}

void Gizmo::Draw() {
	redLine->Draw();
	blueLine->Draw();
	greenLine->Draw();
}

void Gizmo::Destroy() {
	if (redLine){
		redLine->Destroy();
		delete redLine;
	}
	if (blueLine) {
		blueLine->Destroy();
		delete blueLine;
	}
	if (greenLine) {
		greenLine->Destroy();
		delete greenLine;
	}
	if (lineMaterial){
		lineMaterial->Destroy();
		delete lineMaterial;
	}
}

Gizmo::Gizmo(){
	lineMaterial = new Material();
	lineMaterial->LoadShaders("Shaders/SimpleVertex3dShader.shader", "Shaders/LineFragmentShader.shader");
	redLine = new Line3D();
	blueLine = new Line3D();
	greenLine = new Line3D();
	redLine->CreateLine(Vector3().Zero(), Vector3().Right() * 1.5f, Color().Red());
	blueLine->CreateLine(Vector3().Zero(), Vector3().Foward() * 1.5f, Color().Blue());
	greenLine->CreateLine(Vector3().Zero(), Vector3().Up() * 1.5f, Color().Green());
	redLine->SetMaterial(lineMaterial);
	blueLine->SetMaterial(lineMaterial);
	greenLine->SetMaterial(lineMaterial);
}

Gizmo::~Gizmo() {
}
