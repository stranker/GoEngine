#pragma once
#include "Material.h"

class ENGINEDLL_API SpatialMaterial :
    public Material {
private:
    float specular;
    float metallic;
    TextureData diffuseTexture;
    TextureData specularTexture;
    bool defaultCube = false;
public:
    void Use();
    void Destroy() override;
    float GetMetallic() const;
    float GetSpecular() const;
    void SetDiffuseMap(const char* filePath);
    void SetSpecularMap(const char* filePath);
    void SetTextureProperty(string const& propertyName, unsigned int id, unsigned int index);
    void ResetTextureActive();
    TextureData GetDiffuseTexture();
    TextureData GetSpecularTexture();
    void CubeMaterial(float _specular, float _metallic, const char* diffusePath, const char* specularPath);
    SpatialMaterial(float _specular, float _metallic);
    SpatialMaterial();
    ~SpatialMaterial();
};

