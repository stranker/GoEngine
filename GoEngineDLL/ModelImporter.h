#pragma once
#include "Exports.h"
#include "Utils.h"
#include "TextureImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Renderer.h"
#include "SpatialMaterial.h"
#include "Entity.h"

struct Mesh;

class ENGINEDLL_API MeshData : Entity{
private:
	vector<Vector3> position_data;
	vector<Vector3> normal_data;
	vector<Vector2> texCoord_data;
	vector<unsigned int> indices;
	vector<TextureData> textures;
	ADSSpatialMaterial adsMaterial;
public:
	MeshData(vector<Vector3> _position_data, vector<Vector3> _normal_data, vector<Vector2> _texCoord_data, vector<unsigned int> _indices, vector<TextureData> _textures, ADSSpatialMaterial _adsMaterial);
	void Draw(Transform& transform, Renderer::Primitive primitve);
};

class ENGINEDLL_API ModelImporter {
private:
	static void ProcessScene(Mesh& meshInstance, string const& path);
	static void ProcessNode(Mesh& meshInstance, aiNode* node, const aiScene* scene);
	static void ProcessMesh(Mesh& meshInstance, aiMesh* mesh, const aiScene* scene);
	static vector<TextureData> LoadMaterialTextures(Mesh& meshInstance, aiMaterial* mat, aiTextureType type, string typeName);
public:
	static Mesh LoadModel(string const& path);
};

