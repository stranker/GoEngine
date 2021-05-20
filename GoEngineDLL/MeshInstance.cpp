#include "MeshInstance.h"
#include "SpatialMaterial.h"

void Mesh::Draw(Transform& transform, Renderer::Primitive _primitive) {
	for (MeshData meshData : meshes) {
		meshData.Draw(transform, _primitive);
	}
}

void Mesh::Destroy() {
	for (MeshData meshData : meshes) {
		meshData.Destroy();
	}
}

Mesh::Mesh() {
}

void MeshInstance::Draw() {
	Primitive::Draw();
	mesh.Draw(*transform, primitive);
}

MeshInstance::MeshInstance(string const& meshPath) {
	mesh = ModelImporter::LoadModel(meshPath);
	primitive = Renderer::TRIANGLES;
}

void MeshInstance::Destroy() {
	mesh.Destroy();
}
