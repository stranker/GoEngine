#include "Node3D.h"

void Node3D::UpdateChildrensTransform() {
	if (parent) {
		if (parent->Is3DNode()) {
			Node3D* parent3D = (Node3D*)parent;
			*globalTransform = *parent3D->GetGlobalTransform() * *transform;
		}
		else {
			*globalTransform = *transform;
		}
	}
	else {
		*globalTransform = *transform;
	}
	globalBoundingBox = *globalTransform * boundingBox;
	for (Node* node : childrens) {
		Node3D* node3d = (Node3D*)node;
		node3d->UpdateChildrensTransform();
	}
	UpdateGlobalBBoxChildren();
	return OnTransformUpdate();
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

void Node3D::UpdateParentBBox() {
	if (parent) {
		if (parent->GetClass() == "Node3D") {
			Node3D* p = (Node3D*)parent;
			p->UpdateGlobalBBoxChildren();
		}
	}
}

void Node3D::UpdateGlobalBBox() {
	globalBoundingBox = *globalTransform * boundingBox;
}

void Node3D::UpdateGlobalBBoxChildren() {
	if (childrens.empty()) { return UpdateParentBBox(); }
	if (GetClass() == "Node3D") {
		boundingBox = BoundingBox();
	}
	for (Node* child : childrens) {
		if (child->Is3DNode()) {
			Node3D* child3D = (Node3D*)child;
			AddBBox(*child3D->GetTransform() * child3D->GetBBox());
		}
	}
	UpdateGlobalBBox();
	UpdateParentBBox();
}

void Node3D::AddChildren(Node* child) {
	Node::AddChildren(child);
	UpdateChildrensTransform();
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

void Node3D::SetGlobalBBox(const BoundingBox& bbox) {
	globalBoundingBox = bbox;
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

BoundingBox Node3D::GetBBox() const {
	return boundingBox;
}

BoundingBox Node3D::GetGlobalBBox() const {
	return globalBoundingBox;
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

void Node3D::SetBSPEnabled(bool value) {
	bspEnabled = value;
}

bool Node3D::IsBSPEnabled() const {
	return bspEnabled;
}

void Node3D::Draw() {
	if (!CanBeDrawed()) {return CanvasNode::Draw();}
	Profiler::nodesDrawing.push_back(GetName());
	CanvasNode::Draw();
}

void Node3D::ForceDraw(SpatialMaterial* material) {
	Profiler::nodesDrawing.push_back(GetName());
	CanvasNode::ForceDraw(material);
}

bool Node3D::CanBeDrawed() {
	return IsInsideFrustum() && IsVisible() && IsBSPEnabled();
}

void Node3D::SetPrimitive(Renderer::Primitive _primitive) {
	primitive = _primitive;
}

bool Node3D::IsInsideFrustum() {
	return Renderer::GetSingleton()->IsInsideFrustum(*globalTransform, boundingBox);
}

void Node3D::ShowUI() {
	Node::ShowUI();
	UILayer::ShowNode3D(this);
}

void Node3D::HideUI() {
	Node::HideUI();
}

Node3D::Node3D(){
	className = "Node3D";
	SetDefaultName(className);
	transform = new Transform();
	globalTransform = new Transform();
	*globalTransform = *transform;
	is3DNode = true;
}

Node3D::Node3D(const string& _name) : Node3D() {
	name = _name;
}
