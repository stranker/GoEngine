#pragma once
#include "Entity.h"
#include "ModelImporter.h"

class ENGINEDLL_API Mesh : public Entity {
private:
	vector<MeshData> meshes;
	vector<TextureData> texturesLoaded;
	string directory;
public:
	void Draw(unsigned int vao, SpatialMaterial& material, Renderer::Primitive _primitive);
	vector<TextureData> GetTexturesLoaded() { return texturesLoaded; };
	void AddMesh(MeshData meshData) { meshes.push_back(meshData); };
	void AddTexture(TextureData textureData) { texturesLoaded.push_back(textureData); };
	void SetDirectory(string const& dir) { directory = dir; };
	string GetDirectory() { return directory; };
	void SetTexturesLoaded(vector<TextureData> _texturesLoaded) { texturesLoaded = _texturesLoaded; };
	void SetupMesh();
	Mesh();
	~Mesh();
};