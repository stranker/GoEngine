#include "MeshInstance.h"
#include "SpatialMaterial.h"

void Mesh::Draw(Transform& transform, Renderer::Primitive _primitive) {
	for (MeshData meshData : meshes) {
		meshData.Draw(transform, _primitive);
	}
}

Mesh::Mesh() {
}

void MeshInstance::Draw() {
	mesh.Draw(*transform, primitive);
	DrawGizmo();
}

MeshInstance::MeshInstance(string const& meshPath) {
	mesh = ModelImporter::LoadModel(meshPath);
	primitive = Renderer::TRIANGLES;
}

MeshInstance::~MeshInstance() {
}