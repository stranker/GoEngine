#pragma once
#include "Material.h"
#include "ResourceManager.h"

class ENGINEDLL_API SpatialMaterial :
    public Material {
private:
    float specular = 0;
    float metallic = 0;
    Color albedo;
    Texture* albedoTexture;
    Texture* specularTexture;
    bool unshaded = false;
public:
    void Use() override;
    void SetAlbedo(Color color);
    void SetSpecular(float _specular);
    void SetAlbedoMap(const string& filePath);
    void SetSpecularMap(const string& filePath);
    void SetUnshaded(bool value);
    bool IsUnshaded() const;
    Texture* GetAlbedoTexture() { return albedoTexture; };
    Texture* GetSpecularTexture() { return specularTexture; };
    SpatialMaterial(string const& vertexShader, string const& fragmentShader, const string& name);
};

class ENGINEDLL_API ADSSpatialMaterial :
    public Material {
private:
    Texture* diffuseTexture;
    Vector3 ambient = Vector3(0, 0,0);
    Vector3 diffuse = Vector3(0, 0, 0);
    Vector3 specular = Vector3(0, 0, 0);
    float shininess = 0;
public:
    void SetAmbient(Vector3 _ambient) { ambient = _ambient; };
    void SetDiffuse(Vector3 _diffuse) { diffuse = _diffuse; };
    void SetSpecular(Vector3 _specular) {specular = _specular; };
    void SetShininess(float _shininess) {shininess = _shininess ; };
    void SetDiffuseTexture(Texture* _texture) { diffuseTexture = _texture; };
    void Use() override;
    ADSSpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular);
    ADSSpatialMaterial(string const& albedoPath, string const& specularPath);
    ADSSpatialMaterial();
};