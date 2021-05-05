#include "Mesh.h"
#include "Renderer.h"

void Mesh::Draw(unsigned int vao, SpatialMaterial& material, Renderer::Primitive _primitive) {
    for (MeshData meshData : meshes) {
        meshData.Draw(vao, material, _primitive);
    }
}
void Mesh::SetupMesh() {
    for (MeshData meshData : meshes) {
        CreateVertexData(&meshData.position_data[0], meshData.position_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 0);
        CreateVertexData(&meshData.normal_data[0], meshData.normal_data.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 1);
        CreateVertexData(&meshData.texCoord_data[0], meshData.texCoord_data.size() * sizeof(Vector2), 2, Renderer::ARRAY_BUFFER, 2);
        CreateVertexData(&meshData.indices[0], meshData.indices.size() * sizeof(unsigned int), 1, Renderer::ELEMENT_BUFFER, -1);
    }
}

Mesh::Mesh() {
}


Mesh::~Mesh() {
}
