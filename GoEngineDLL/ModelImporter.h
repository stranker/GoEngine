#pragma once
#include "ResourceManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Renderer.h"
#include "SpatialMaterial.h"
#include "Node3D.h"

class ENGINEDLL_API MeshData : public Resource {
public:
	vector<Vector3> position_data;
	vector<Vector3> normal_data;
	vector<Vector2> texCoord_data;
	vector<unsigned int> indices;
	ADSSpatialMaterial* adsMaterial;
	MeshData() {};
};

class ENGINEDLL_API ModelImporter {
private:
	static string tempOutDirectory;
	static vector<Texture*> tempTextures;
	static Node3D* ProcessScene(string const& path);
	static void ProcessNode(Node3D* node3d, aiNode* node, const aiScene* scene);
	static MeshData ProcessMesh(aiMesh* mesh, const aiScene* scene);
	static Texture* LoadMaterialTexture(aiMaterial* mat, aiTextureType type, string typeName);
public:
	static Node3D* LoadModel(string const& path);
};

