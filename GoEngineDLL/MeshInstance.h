#pragma once
#include "Primitive.h"
#include "ModelImporter.h"

struct ENGINEDLL_API Mesh {
private:
	vector<MeshData> meshes;
	vector<TextureData> texturesLoaded;
	string directory;
public:
	void Draw(Transform& transform, Renderer::Primitive _primitive);
	vector<TextureData> GetTexturesLoaded() { return texturesLoaded; };
	void AddMesh(MeshData meshData) { meshes.push_back(meshData); };
	void AddTexture(TextureData textureData) { texturesLoaded.push_back(textureData); };
	void SetDirectory(string const& dir) { directory = dir; };
	string GetDirectory() { return directory; };
	void SetTexturesLoaded(vector<TextureData> _texturesLoaded) { texturesLoaded = _texturesLoaded; };
	vector<MeshData> GetMeshes() const { return meshes; };
	Mesh();
};

class ENGINEDLL_API MeshInstance :
    public Primitive {
protected:
    Mesh mesh;
public:
    void Draw() override;
    MeshInstance(string const &meshPath);
    ~MeshInstance();
};

