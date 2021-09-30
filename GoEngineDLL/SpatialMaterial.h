#pragma once
#include "Material.h"
#include "ResourceManager.h"

class ENGINEDLL_API SpatialMaterial :
    public Material {
private:
    map<string, Texture*> textures;
    map<string, Vector3> floatValues;
    map<string, Vector3> vec3Values;
    float specular = 0;
    float metallic = 0;
    Texture* diffuseTexture;
    Texture* specularTexture;
protected:
    void SetDiffuseMap(const char* filePath);
    void SetSpecularMap(const char* filePath);
public:
    void Use() override;
    void CreateMaterial(float _specular, float _metallic, string const& diffusePath, string const& specularPath);
    void AddTexture(const string& name, Texture* texture);
    void AddFloat(const string& name, float value, float min, float max);
    void AddVector3(const string& name, Vector3 value);
    map<string, Texture*> GetTextures() { return textures; };
    map<string, Vector3> GetFloats() { return floatValues; };
    SpatialMaterial() {};
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
    void CreateMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess, Texture* _diffuseTexture);
    ADSSpatialMaterial() {};
};