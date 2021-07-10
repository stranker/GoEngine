#include "Node3D.h"
#include "Line3D.h"

void Gizmo3D::Draw(const Transform& _transform) {
	if (!IsVisible()) { return; };
	if (!Renderer::GetSingleton()->IsInsideFrustum(_transform.GetPosition())) { return; };
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
	Line3D* redLine, *blueLine, *greenLine;
	redLine = new Line3D(Vector3().Zero(), Vector3().Right() * 1.5f, Color().Red());
	blueLine = new Line3D(Vector3().Zero(), Vector3().Back() * 1.5f, Color().Blue());
	greenLine = new Line3D(Vector3().Zero(), Vector3().Up() * 1.5f, Color().Green());
	lines.push_back(redLine);
	lines.push_back(blueLine);
	lines.push_back(greenLine);
	SetVisible(false);
}

void Node3D::UpdateChildrensTransform() {
	if (parent){
		if (parent->GetClass() == "Node3D" || parent->GetClass() == "MeshInstance") {
			Node3D* parent3D = (Node3D*)parent;
			*globalTransform = *parent3D->GetGlobalTransform() * *transform;
		}
		else {
			*globalTransform = *transform;
		}
	}
	else{
		*globalTransform = *transform;
	}
	for (Node* node : childrens){
		Node3D* node3d = (Node3D*)node;
		node3d->UpdateChildrensTransform();
	}
	return OnTransformUpdate();
}

void Node3D::SetPosition(Vector3 position) {
	transform->SetPosition(position);
	UpdateChildrensTransform();
	UpdateBBox();
}

void Node3D::Translate(Vector3 position) {
	transform->Translate(position);
	UpdateChildrensTransform();
	UpdateBBox();
}

void Node3D::SetEulerAngles(Vector3 eulerAngles) {
	transform->SetEulerAngles(eulerAngles);
	UpdateChildrensTransform();
	UpdateBBox();
}

void Node3D::Rotate(float angle, Vector3 axis) {
	transform->SetRotation(angle, axis);
	UpdateChildrensTransform();
	UpdateBBox();
}

void Node3D::UpdateParentBBox() {
	if (parent) {
		if (parent->GetClass() == "Node3D") {
			Node3D* p = (Node3D*)parent;
			p->UpdateGlobalBBoxChildren();
		}
	}
}

void Node3D::UpdateGlobalBBox() {
	globalBoundingBox = *transform * boundingBox;
}

void Node3D::UpdateGlobalBBoxChildren() {
	boundingBox = GetClass() == "Node3D" ? BoundingBox() : boundingBox;
	globalBoundingBox = BoundingBox();
	for (Node* child : childrens) {
		if (child->GetClass() == "Node3D" || child->GetClass() == "MeshInstance") {
			Node3D* child3D = (Node3D*)child;
			if (GetClass() == "Node3D") {
				AddBBox(child3D->GetGlobalBBox());
			}
			AddGlobalBBox(*child3D->GetTransform() * child3D->GetBBox());
		}
	}
	UpdateParentBBox();
}

void Node3D::AddChildren(Node* child) {
	Node::AddChildren(child);
	Node3D* c = (Node3D*)child;
	AddBBox(c->GetBBox());
	AddGlobalBBox(c->GetGlobalBBox());
	UpdateParentBBox();
}

void Node3D::AddBBox(const BoundingBox& bbox) {
	BoundingBox newAABB;
	newAABB = BoundingBox(boundingBox, bbox);
	boundingBox = newAABB;
}

void Node3D::AddGlobalBBox(const BoundingBox& bbox) {
	BoundingBox newAABB;
	newAABB = BoundingBox(globalBoundingBox, bbox);
	globalBoundingBox = newAABB;
}

void Node3D::SetBBox(const BoundingBox& bbox) {
	boundingBox = bbox;
}

void Node3D::RotateX(float angle) {
	transform->RotateX(angle);
	UpdateChildrensTransform();
	UpdateBBox();
}
void Node3D::RotateY(float angle) {
	transform->RotateY(angle);
	UpdateChildrensTransform();
	UpdateBBox();
}

void Node3D::RotateZ(float angle) {
	transform->RotateZ(angle);
	UpdateChildrensTransform();
	UpdateBBox();
}

void Node3D::SetScale(Vector3 scale) {
	transform->SetScale(scale);
	UpdateChildrensTransform();
	UpdateBBox();
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

BoundingBox Node3D::GetBBox() const {
	return boundingBox;
}

BoundingBox Node3D::GetGlobalBBox() const {
	return globalBoundingBox;
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
	if (!IsInsideFrustum()) {
		return;
	}
	CanvasNode::Draw();
}

bool Node3D::IsInsideFrustum() {
	return Renderer::GetSingleton()->IsInsideFrustum(*globalTransform, boundingBox);
}

void Node3D::UpdateBBox() {
	UpdateGlobalBBox();
	UpdateParentBBox();
}

void Node3D::ShowUI() {
	Node::ShowUI();
	gizmo->SetVisible(true);
	UILayer::ShowNode3D(this);
}

void Node3D::HideUI() {
	Node::HideUI();
	gizmo->SetVisible(false);
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
