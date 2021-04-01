#include "Entity3D.h"

void Entity3D::SetPosition(Vector3 position) {
	transform->SetPosition(position);
}

void Entity3D::Translate(Vector3 position) {
	transform->Translate(position);
}

void Entity3D::Rotate(Vector3  rotation) {
	transform->RotateX(rotation.x);
	transform->RotateY(rotation.y);
	transform->RotateZ(rotation.z);
}

void Entity3D::Rotate(float angle, Vector3 axis) {
	transform->SetRotation(angle, axis);
}

void Entity3D::SetScale(Vector3 scale) {
	transform->SetScale(scale);
}

Vector3 Entity3D::GetPosition() const {
	return transform->GetPosition();
}

Vector3 Entity3D::GetRotation() const {
	return transform->GetRotation();
}

Vector3 Entity3D::GetScale() const {
	return transform->GetScale();
}

void Entity3D::Destroy() {
	cout << "Destroy Entity3D" << endl;
	if (renderer) {
		for (Renderer::VertexData vertexData : vectorVertexData) {
			renderer->DeleteBuffer(vertexData.vbo);
		}
	}
	if (material){
		material->Destroy();
		delete material;
	}
}

Transform* Entity3D::GetTransform() {
	return transform;
}

Entity3D::Entity3D(Renderer* _renderer) : Entity(_renderer) {
}

Entity3D::~Entity3D() {
}
