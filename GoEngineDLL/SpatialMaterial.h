#pragma once
#include "Material.h"

class ENGINEDLL_API SpatialMaterial :
    public Material {
private:
    float specular;
    float metallic;
    TextureData diffuseTexture;
    TextureData specularTexture;
    unsigned int diffuseMap;
    unsigned int specularMap;
public:
    void Use();
    float GetMetallic() const;
    float GetSpecular() const;
    void SetDiffuseMap(const char* filePath, ImageType imageType);
    void SetSpecularMap(const char* filePath, ImageType imageType);
    void SetTextureProperty(const char* property, unsigned int value, unsigned int textureId);
    TextureData GetDiffuseTexture();
    TextureData GetSpecularTexture();
    SpatialMaterial(float _specular, float _metallic);
    SpatialMaterial();
    ~SpatialMaterial();
};

