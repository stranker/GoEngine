#pragma once
#include "Utils.h"

class Material;
class SpatialMaterial;
class ADSSpatialMaterial;
class Texture;
class Node3D;
class Shader;

class ENGINEDLL_API ResourceManager {
private:
	ResourceManager() { singleton = this; };
	static ResourceManager* singleton;

	static int resourceCount;

	static map<string, Texture*> textures;
	static map<string, SpatialMaterial*> spatialMaterials;
	static map<string, ADSSpatialMaterial*> adsSpatialMaterials;
	static map<string, Material*> materials;
	static map<string, Node3D*> models;
	static map<string, Shader*> shaders;

	static Texture* LoadTextureFromFile(string const& path);
	static SpatialMaterial* _LoadSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, const string& name);
	static ADSSpatialMaterial* _LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, const string& name);
	static Material* _LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader, const string& name);
	static Node3D* LoadModel(string const& filePath);
	static Shader* LoadShader(const string& vertexPath, const string& fragmentPath);
public:
	static ResourceManager* GetSingleton();
	static Texture* LoadTexture(string const& path, string const& name);
	static Texture* GetTexture(string const& name);
	static SpatialMaterial* LoadSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name);
	static SpatialMaterial* GetSpatialMaterial(string const& name);
	static ADSSpatialMaterial* LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name);
	static ADSSpatialMaterial* GetADSSpatialMaterial(string const& name);
	static Material* LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name);
	static Material* GetMaterial(string const& name);
	static Node3D* LoadModel(string const& path, string const& name);
	static Node3D* GetModel(string const& name);
	static Shader* LoadShader(const string& vertexPath, const string& fragmentPath, const string& name);
	static int GetResourcesCount();
	static void Clear();
};