#include "ResourceManager.h"
#include "Renderer.h"
#include "TextureImporter.h"
#include "SpatialMaterial.h"
#include "ModelImporter.h"
#include "MeshInstance.h"

ResourceManager* ResourceManager::singleton = NULL;
map<string, Texture*> ResourceManager::textures;
map<string, SpatialMaterial*> ResourceManager::spatialMaterials;
map<string, ADSSpatialMaterial*> ResourceManager::adsSpatialMaterials;
map<string, Material*> ResourceManager::materials;
map<string, Node3D*> ResourceManager::models;
int ResourceManager::resourceCount = 0;

Texture* ResourceManager::LoadTextureFromFile(string const& path) {
    Texture* texture = new Texture();
    *texture = TextureImporter::LoadTexture(path.c_str());
    resourceCount++;
    texture->SetID(resourceCount);
    return texture;
}

SpatialMaterial* ResourceManager::LoadSpatialMaterialFromFile(string const& pathVertexShader, string const& pathFragmentShader) {
    SpatialMaterial* sm = new SpatialMaterial();
    sm->LoadShaders(pathVertexShader, pathFragmentShader);
    resourceCount++;
    sm->SetID(resourceCount);
    return sm;
}

ADSSpatialMaterial* ResourceManager::LoadADSSpatialMaterialFromFile(string const& pathVertexShader, string const& pathFragmentShader) {
    ADSSpatialMaterial* sm = new ADSSpatialMaterial();
    sm->LoadShaders(pathVertexShader, pathFragmentShader);
    resourceCount++;
    sm->SetID(resourceCount);
    return sm;
}

Material* ResourceManager::LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader) {
    Material* mat = new Material();
    mat->LoadShaders(pathVertexShader, pathFragmentShader);
    resourceCount++;
    mat->SetID(resourceCount);
    return mat;
}

Node3D* ResourceManager::LoadModel(string const& filePath) {
    Node3D* model = new Node3D();
    model = ModelImporter::LoadModel(filePath);
    resourceCount++;
    return model;
}

ResourceManager* ResourceManager::GetSingleton() {
    return singleton;
}

Texture* ResourceManager::LoadTexture(string const& path, string const& name) {
    if (textures.find(name) == textures.end()) {
        textures[name] = LoadTextureFromFile(path.c_str());
        textures[name]->SetName(name);
    }
    return textures[name];
}

SpatialMaterial* ResourceManager::LoadSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    spatialMaterials[name] = LoadSpatialMaterialFromFile(pathVertexShader, pathFragmentShader);
    spatialMaterials[name]->SetName(name);
    return spatialMaterials[name];
}

ADSSpatialMaterial* ResourceManager::LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    adsSpatialMaterials[name] = LoadADSSpatialMaterialFromFile(pathVertexShader, pathFragmentShader);
    adsSpatialMaterials[name]->SetName(name);
    return adsSpatialMaterials[name];
}

Texture* ResourceManager::GetTexture(string const& name) {
    return textures[name];
}

SpatialMaterial* ResourceManager::GetSpatialMaterial(string const& name) {
    return spatialMaterials[name];
}

ADSSpatialMaterial* ResourceManager::GetADSSpatialMaterial(string const& name) {
    return adsSpatialMaterials[name];
}

Material* ResourceManager::LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    materials[name] = LoadMaterial(pathVertexShader, pathFragmentShader);
    materials[name]->SetName(name);
    return materials[name];
}

Material* ResourceManager::GetMaterial(string const& name) {
    return materials[name];
}

Node3D* ResourceManager::LoadModel(string const& path, string const& name) {
    if (models.find(name) == models.end()) {
        models[name] = LoadModel(path);
        models[name]->SetName(name);
    }
    return models[name];
}

Node3D* ResourceManager::GetModel(string const& name) {
    return models[name];
}

int ResourceManager::GetResourcesCount() {
    return resourceCount;
}

void ResourceManager::Clear() {
    for (auto iter : textures) {
        Renderer::GetSingleton()->DeleteTexture(iter.second->GetTextureID());
    }
    textures.clear();
    for (auto iter : spatialMaterials) {
        Renderer::GetSingleton()->DeleteShader(iter.second->GetID());
    }
    spatialMaterials.clear();
    for (auto iter : adsSpatialMaterials) {
        Renderer::GetSingleton()->DeleteShader(iter.second->GetID());
    }
    adsSpatialMaterials.clear();
    for (auto iter : materials) {
        Renderer::GetSingleton()->DeleteShader(iter.second->GetID());
    }
    materials.clear();
    resourceCount = 0;
}