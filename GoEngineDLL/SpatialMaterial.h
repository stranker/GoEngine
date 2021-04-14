#pragma once
#include "Material.h"
class ENGINEDLL_API SpatialMaterial :
    public Material {

private:
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float shininess;
public:
    void Use();
    Vector3 GetAmbient() const;
    Vector3 GetDiffuse() const;
    Vector3 GetSpecular() const;
    float GetShininess() const;
    SpatialMaterial(Vector3 _ambient, Vector3 _diffuse, Vector3 _specular, float _shininess);
    SpatialMaterial();
    ~SpatialMaterial();
};

