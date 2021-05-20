#pragma once
#include "Utils.h"

class Material;
class SpatialMaterial;
class ADSSpatialMaterial;
class Texture;
struct Mesh;

class ENGINEDLL_API ResourceManager {
private:
	ResourceManager() { singleton = this; };
	static ResourceManager* singleton;

	static map<string, Texture> textures;
	static map<string, SpatialMaterial> spatialMaterials;
	static map<string, ADSSpatialMaterial> adsSpatialMaterials;
	static map<string, Material> materials;
	static map<string, Mesh> models;

	static Texture LoadTextureFromFile(string const& path);
	static SpatialMaterial LoadSpatialMaterialFromFile(string const& pathVertexShader, string const& pathFragmentShader);
	static ADSSpatialMaterial LoadADSSpatialMaterialFromFile(string const& pathVertexShader, string const& pathFragmentShader);
	static Material LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader);
	static Mesh LoadModel(string const& path);
public:
	static ResourceManager* GetSingleton();
	static Texture LoadTexture(string const& path, string const& name);
	static Texture GetTexture(string const& name);
	static SpatialMaterial LoadSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name);
	static SpatialMaterial GetSpatialMaterial(string const& name);
	static ADSSpatialMaterial LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name);
	static ADSSpatialMaterial GetADSSpatialMaterial(string const& name);
	static Material LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name);
	static Material GetMaterial(string const& name);
	static Mesh LoadModel(string const& path, string const& name);
	static Mesh GetModel(string const& name);
	static void Clear();
};