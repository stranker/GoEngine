#include "MeshInstance.h"
#include "SpatialMaterial.h"

void MeshInstance::Draw() {
	BindVertexArray();
	ADSSpatialMaterial* material = mesh->adsMaterial;
	if (material) {
		material->Use();
		material->SetMat4("model", globalTransform->GetTransform());
		material->SetMat4("view", Renderer::GetSingleton()->GetCamera()->GetView());
		material->SetMat4("projection", Renderer::GetSingleton()->GetCamera()->GetProjection());
		material->SetVec3("viewPos", Renderer::GetSingleton()->GetCamera()->GetTransform().GetPosition());
	}
	Renderer::GetSingleton()->Draw(primitive, mesh->indices.size(), true);
	Primitive::Draw();
}

void MeshInstance::SetMesh(MeshData* _mesh) {
	mesh = _mesh;
	CreateVertexArrayID();
	BindVertexArray();
	CreateVertexData(&_mesh->position_data[0], _mesh->position_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 0);
	if (!_mesh->normal_data.empty()) {
		CreateVertexData(&_mesh->normal_data[0], _mesh->normal_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 1);
	}
	if (!_mesh->texCoord_data.empty()) {
		CreateVertexData(&_mesh->texCoord_data[0], _mesh->texCoord_data.size() * sizeof(Vector2), 2, Renderer::ARRAY_BUFFER, 2);
	}
	CreateVertexData(&_mesh->indices[0], _mesh->indices.size() * sizeof(unsigned int), 1, Renderer::ELEMENT_BUFFER, -1);
	BindVertexObjects();
	primitive = Renderer::TRIANGLES;
}

MeshInstance::MeshInstance() {
	className = "MeshInstance";
	SetDefaultName(className);
}
