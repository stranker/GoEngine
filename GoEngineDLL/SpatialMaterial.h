#pragma once
#include "Material.h"

class ENGINEDLL_API SpatialMaterial :
    public Material {
private:
    float specular;
    float metallic;
    TextureData diffuseTexture;
    TextureData specularTexture;
    void SetDiffuseMap(const char* filePath);
    void SetSpecularMap(const char* filePath);
public:
    void Use() override;
    void SetTextureProperty(string const& propertyName, unsigned int id, unsigned int index);
    void ResetTextureActive();
    SpatialMaterial(float _specular, float _metallic, const char* diffusePath, const char* specularPath);
    SpatialMaterial(float _specular, float _metallic);
    SpatialMaterial(const char* pathVertexShader, const char* pathFragmentShader);
    SpatialMaterial();
};

class ENGINEDLL_API ADSSpatialMaterial :
    public SpatialMaterial {
private:
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float shininess;
public:
    void SetAmbient(Vector3 _ambient) { ambient = _ambient; };
    void SetDiffuse(Vector3 _diffuse) { diffuse = _diffuse; };
    void SetSpecular(Vector3 _specular) {specular = _specular; };
    void SetShininess(float _shininess) {shininess = _shininess ; };
    void Use() override;
    ADSSpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess);
    ADSSpatialMaterial();
};