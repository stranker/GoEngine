#include "ResourceManager.h"
#include "Renderer.h"
#include "TextureImporter.h"
#include "SpatialMaterial.h"
#include "ModelImporter.h"
#include "MeshInstance.h"
#include "Shader.h"

ResourceManager* ResourceManager::singleton = NULL;
map<string, Texture*> ResourceManager::textures;
map<string, SpatialMaterial*> ResourceManager::spatialMaterials;
map<string, ADSSpatialMaterial*> ResourceManager::adsSpatialMaterials;
map<string, Material*> ResourceManager::materials;
map<string, Node3D*> ResourceManager::models;
map<string, Shader*> ResourceManager::shaders;
int ResourceManager::resourceCount = 0;

Texture* ResourceManager::LoadTextureFromFile(string const& path) {
    Texture* texture = new Texture();
    *texture = TextureImporter::LoadTexture(path.c_str());
    resourceCount++;
    texture->SetID(resourceCount);
    return texture;
}

SpatialMaterial* ResourceManager::_LoadSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, const string& name) {
    SpatialMaterial* sm = new SpatialMaterial(pathVertexShader, pathFragmentShader, name);
    resourceCount++;
    sm->SetID(resourceCount);
    return sm;
}

ADSSpatialMaterial* ResourceManager::_LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, const string& name) {
    ADSSpatialMaterial* sm = new ADSSpatialMaterial();
    resourceCount++;
    sm->SetID(resourceCount);
    return sm;
}

Material* ResourceManager::_LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader, const string& name) {
    Material* mat = new Material(pathVertexShader, pathFragmentShader, name);
    resourceCount++;
    mat->SetID(resourceCount);
    return mat;
}

Node3D* ResourceManager::LoadModel(string const& filePath) {
    resourceCount++;
    return ModelImporter::LoadModel(filePath);;
}

Shader* ResourceManager::LoadShader(const string& vertexPath, const string& fragmentPath) {
    Shader* shader = new Shader(vertexPath, fragmentPath);
    resourceCount++;
    shader->SetID(resourceCount);
    return shader;
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
    if (spatialMaterials.find(name) == spatialMaterials.end()) {
        spatialMaterials[name] = _LoadSpatialMaterial(pathVertexShader, pathFragmentShader, name);
        spatialMaterials[name]->SetName(name);
    }
    return spatialMaterials[name];
}

ADSSpatialMaterial* ResourceManager::LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    if (adsSpatialMaterials.find(name) == adsSpatialMaterials.end()) {
        adsSpatialMaterials[name] = _LoadADSSpatialMaterial(pathVertexShader, pathFragmentShader, name);
        adsSpatialMaterials[name]->SetName(name);
    }
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
    if (materials.find(name) == materials.end()) {
        materials[name] = _LoadMaterial(pathVertexShader, pathFragmentShader, name);
        materials[name]->SetName(name);
    }
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

Shader* ResourceManager::LoadShader(const string& vertexPath, const string& fragmentPath, const string& name) {
    if (shaders.find(name) == shaders.end()) {
        shaders[name] = LoadShader(vertexPath, fragmentPath);
        shaders[name]->SetName(name);
    }
    return shaders[name];
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