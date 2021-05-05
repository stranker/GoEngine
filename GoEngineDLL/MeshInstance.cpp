#include "MeshInstance.h"
#include "SpatialMaterial.h"

void MeshInstance::Draw() {
	if (spatialMaterial){
		spatialMaterial->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(transform->GetTransform()));
		mesh.Draw(GetVertexArrayID(), *spatialMaterial, primitive);
	}
	DrawGizmo();
}

void MeshInstance::Destroy() {
	if (spatialMaterial) {
		spatialMaterial->Destroy();
	}
}

MeshInstance::MeshInstance(string const& meshPath) {
	spatialMaterial = new SpatialMaterial();
	spatialMaterial->LoadShaders("Shaders/SpatialMesh.vs", "Shaders/SpatialMesh.fs");
	CreateVertexArrayID();
	mesh = ModelImporter::LoadModel(meshPath);
	mesh.SetupMesh();
	SetVertexData(mesh.GetVectorVertexData());
	BindVertexObjects();
	primitive = Renderer::TRIANGLES;
}

MeshInstance::~MeshInstance() {
}
