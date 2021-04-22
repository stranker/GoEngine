#pragma once
#include "Material.h"

class ENGINEDLL_API SpatialMaterial :
    public Material {
private:
    const int LIGHT_SHADER_VERSION = 2;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float shininess;
    TextureData diffuseTexture;
    TextureData specularTexture;
    unsigned int diffuseMap;
    unsigned int specularMap;
public:
    void Use();
    Vector3 GetAmbient() const;
    Vector3 GetDiffuse() const;
    Vector3 GetSpecular() const;
    float GetShininess() const;
    void SetDiffuseMap(const char* filePath, ImageType imageType);
    void SetSpecularMap(const char* filePath, ImageType imageType);
    void SetTextureProperty(const char* property, unsigned int value, unsigned int textureId);
    TextureData GetDiffuseTexture();
    TextureData GetSpecularTexture();
    SpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess);
    SpatialMaterial();
    ~SpatialMaterial();
};

