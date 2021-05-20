#pragma once
#include "Primitive.h"
#include "ModelImporter.h"

class ENGINEDLL_API Mesh :
	public Entity
{
private:
	vector<MeshData> meshes;
	vector<Texture> texturesLoaded;
	string directory;
public:
	void Draw(Transform& transform, Renderer::Primitive _primitive);
	void Destroy();
	vector<Texture> GetTexturesLoaded() { return texturesLoaded; };
	void AddMesh(MeshData meshData) { meshes.push_back(meshData); };
	void AddTexture(Texture textureData) { texturesLoaded.push_back(textureData); };
	void SetDirectory(string const& dir) { directory = dir; };
	string GetDirectory() { return directory; };
	void SetTexturesLoaded(vector<Texture> _texturesLoaded) { texturesLoaded = _texturesLoaded; };
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
	void Destroy() override;
};

