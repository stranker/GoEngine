#include "ResourceManager.h"
#include "Renderer.h"
#include "TextureImporter.h"
#include "SpatialMaterial.h"

ResourceManager* ResourceManager::singleton = NULL;
map<string, Texture> ResourceManager::textures;
map<string, SpatialMaterial> ResourceManager::spatialMaterials;
map<string, ADSSpatialMaterial> ResourceManager::adsSpatialMaterials;
map<string, Material> ResourceManager::materials;

Texture ResourceManager::LoadTextureFromFile(string const& path) {
    Texture texture = TextureImporter::LoadTexture(path.c_str());
    return texture;
}

SpatialMaterial ResourceManager::LoadSpatialMaterialFromFile(string const& pathVertexShader, string const& pathFragmentShader) {
    SpatialMaterial sm;
    sm.LoadShaders(pathVertexShader.c_str(), pathFragmentShader.c_str());
    return sm;
}

ADSSpatialMaterial ResourceManager::LoadADSSpatialMaterialFromFile(string const& pathVertexShader, string const& pathFragmentShader) {
    ADSSpatialMaterial sm;
    sm.LoadShaders(pathVertexShader.c_str(), pathFragmentShader.c_str());
    return sm;
}

Material ResourceManager::LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader) {
    Material mat;
    mat.LoadShaders(pathVertexShader.c_str(), pathFragmentShader.c_str());
    return mat;
}

ResourceManager* ResourceManager::GetSingleton() {
    return singleton;
}

Texture ResourceManager::LoadTexture(string const& path, string const& name) {
    textures[name] = LoadTextureFromFile(path.c_str());
    return textures[name];
}

SpatialMaterial ResourceManager::LoadSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    spatialMaterials[name] = LoadSpatialMaterialFromFile(pathVertexShader, pathFragmentShader);
    return spatialMaterials[name];
}

ADSSpatialMaterial ResourceManager::LoadADSSpatialMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    adsSpatialMaterials[name] = LoadADSSpatialMaterialFromFile(pathVertexShader, pathFragmentShader);
    return adsSpatialMaterials[name];
}

Texture ResourceManager::GetTexture(string const& name) {
    return textures[name];
}

SpatialMaterial ResourceManager::GetSpatialMaterial(string const& name) {
    return spatialMaterials[name];
}

ADSSpatialMaterial ResourceManager::GetADSSpatialMaterial(string const& name) {
    return adsSpatialMaterials[name];
}

Material ResourceManager::LoadMaterial(string const& pathVertexShader, string const& pathFragmentShader, string const& name) {
    materials[name] = LoadMaterial(pathVertexShader, pathFragmentShader);
    return materials[name];
}

Material ResourceManager::GetMaterial(string const& name) {
    return materials[name];
}

void ResourceManager::Clear() {
    for (auto iter : textures) {
        Renderer::GetSingleton()->DeleteTexture(iter.second.GetTextureID());
    }
    for (auto iter : spatialMaterials) {
        Renderer::GetSingleton()->DeleteShader(iter.second.GetID());
    }
    for (auto iter : adsSpatialMaterials) {
        Renderer::GetSingleton()->DeleteShader(iter.second.GetID());
    }
    for (auto iter : materials) {
        Renderer::GetSingleton()->DeleteShader(iter.second.GetID());
    }
}