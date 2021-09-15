#pragma once
#include "ResourceManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Renderer.h"
#include "SpatialMaterial.h"
#include "Node3D.h"
#include "Quad.h"

class MeshInstance;

class ENGINEDLL_API MeshData : public Resource {
public:
	vector<Vector3> position_data;
	vector<Vector3> normal_data;
	vector<Vector2> texCoord_data;
	BoundingBox boundingBox;
	vector<unsigned int> indices;
	ADSSpatialMaterial* adsMaterial;
	void CreateBBox();
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
	static MeshInstance* CreateMeshInstance(aiVector3D _trans, aiVector3D _rot, aiVector3D _scl, MeshData* _meshData, const string& name);
	static Node3D* CreateNode(aiVector3D _trans, aiVector3D _rot, aiVector3D _scl, const string& _name);
public:
	static Node3D* LoadModel(string const& path);
};

