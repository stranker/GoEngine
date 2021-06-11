#include "Node3D.h"
#include "Line3D.h"

void Gizmo3D::Draw(const Transform& _transform) {
	if (!IsVisible()) { return; };
	for (size_t i = 0; i < lines.size(); i++) {
		lines.at(i)->Draw(_transform);
	}
}

void Gizmo3D::Destroy() {
	for (size_t i = 0; i < lines.size(); i++) {
		delete lines.at(i);
	}
	if (!lines.empty()) {
		lines.clear();
	}
}

Gizmo3D::Gizmo3D() {
	lineMaterial = ResourceManager::LoadMaterial("Shaders/SimpleVertex3dShader.shader", "Shaders/LineFragmentShader.shader", "lineMaterial");
	Line3D* redLine, *blueLine, *greenLine;
	redLine = new Line3D(Vector3().Zero(), Vector3().Right() * 1.5f, Color().Red(), lineMaterial);
	blueLine = new Line3D(Vector3().Zero(), Vector3().Foward() * 1.5f, Color().Blue(), lineMaterial);
	greenLine = new Line3D(Vector3().Zero(), Vector3().Up() * 1.5f, Color().Green(), lineMaterial);
	lines.push_back(redLine);
	lines.push_back(blueLine);
	lines.push_back(greenLine);
}

void Node3D::UpdateChildrensTransform() {
	if (parent){
		Node3D* parent3D = (Node3D*)parent;
		*globalTransform = *parent3D->GetGlobalTransform() * *transform;
	}
	else{
		*globalTransform = *transform;
	}
	for (Node* node : childrens){
		Node3D* node3d = (Node3D*)node;
		node3d->UpdateChildrensTransform();
	}
}

void Node3D::SetPosition(Vector3 position) {
	transform->SetPosition(position);
	UpdateChildrensTransform();
}

void Node3D::Translate(Vector3 position) {
	transform->Translate(position);
	UpdateChildrensTransform();
}

void Node3D::SetEulerAngles(Vector3 eulerAngles) {
	transform->SetEulerAngles(eulerAngles);
	UpdateChildrensTransform();
}

void Node3D::Rotate(float angle, Vector3 axis) {
	transform->SetRotation(angle, axis);
	UpdateChildrensTransform();
}

void Node3D::RotateX(float angle) {
	transform->RotateX(angle);
	UpdateChildrensTransform();
}
void Node3D::RotateY(float angle) {
	transform->RotateY(angle);
	UpdateChildrensTransform();
}

void Node3D::RotateZ(float angle) {
	transform->RotateZ(angle);
	UpdateChildrensTransform();
}

void Node3D::SetScale(Vector3 scale) {
	transform->SetScale(scale);
	UpdateChildrensTransform();
}

void Node3D::LookAt(Vector3 _position, Vector3 _target, Vector3 _upVector) {
	transform->LookAt(_position, _target, _upVector);
	UpdateChildrensTransform();
}

void Node3D::LookAt(Vector3 _target, Vector3 _upVector) {
	LookAt(transform->GetPosition(), _target, _upVector);
}

void Node3D::LookAt(Vector3 _target) {
	LookAt(_target, Vector3().Up());
}

void Node3D::SetGizmoVisible(bool gizmoVisible) {
	gizmo->SetVisible(gizmoVisible);
}

Vector3 Node3D::GetPosition() const {
	return transform->GetPosition();
}

Vector3 Node3D::GetRotation() const {
	return transform->GetRotation();
}

Vector3 Node3D::GetScale() const {
	return transform->GetScale();
}

Transform* Node3D::GetTransform() {
	return transform;
}

Transform* Node3D::GetGlobalTransform() {
	return globalTransform;
}

void Node3D::Draw() {
	gizmo->Draw(*globalTransform);
	CanvasNode::Draw();
}

Node3D::Node3D(){
	className = "Node3D";
	SetDefaultName(className);
	gizmo = new Gizmo3D();
	transform = new Transform();
	globalTransform = new Transform();
	*globalTransform = *transform;
}

Node3D::Node3D(const string& _name) : Node3D() {
	name = _name;
}
