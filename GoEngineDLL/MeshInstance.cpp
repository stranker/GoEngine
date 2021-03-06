#include "MeshInstance.h"
#include "SpatialMaterial.h"

void MeshInstance::Draw() {
	if (!IsVisible()) { return Node3D::Draw(); }
	if (!IsInsideFrustum()) {return Node3D::Draw(); }
	if (mesh->adsMaterial) {
		mesh->adsMaterial->Use();
		mesh->adsMaterial->SetMat4("model", globalTransform->GetTransform());
		mesh->adsMaterial->SetMat4("view", Renderer::GetSingleton()->GetCamera()->GetView());
		mesh->adsMaterial->SetMat4("projection", Renderer::GetSingleton()->GetCamera()->GetProjection());
		mesh->adsMaterial->SetVec3("viewPos", Renderer::GetSingleton()->GetCameraTransform()->GetPosition());
	}
	Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, mesh->indices.size(), true);
	Node3D::Draw();
}

void MeshInstance::SetMesh(MeshData* _mesh) {
	mesh = _mesh;
	CreateVertexArrayID();
	BindVertexArray();
	CreateVertexData(&mesh->position_data[0], mesh->position_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 0);
	if (!mesh->normal_data.empty()) {
		CreateVertexData(&mesh->normal_data[0], mesh->normal_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 1);
	}
	if (!mesh->texCoord_data.empty()) {
		CreateVertexData(&mesh->texCoord_data[0], mesh->texCoord_data.size() * sizeof(Vector2), 2, Renderer::ARRAY_BUFFER, 2);
	}
	if (!mesh->indices.empty()) {
		CreateVertexData(&mesh->indices[0], mesh->indices.size() * sizeof(unsigned int), 1, Renderer::ELEMENT_BUFFER, -1);
	}
	BindVertexObjects();
	primitive = Renderer::TRIANGLES;
	SetBBox(mesh->boundingBox);
	SetGlobalBBox(mesh->boundingBox);
}

MeshInstance::MeshInstance() {
	className = "MeshInstance";
	SetDefaultName(className);
}
