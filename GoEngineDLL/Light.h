#pragma once
#include "Primitive.h"
class ENGINEDLL_API Light :
    public Primitive {
private:
    Vector3 lightColor;
    Vector3 ambient;
    Vector3 diffuse;
    Vector3 specular;
    float range;
    const int drawVertices = 12 * 3;
public:
    void CreateLight(Vector3 _color, Vector3 _ambient, Vector3 _diffuse, Vector3 _specular);
    void Draw() override;
    void SetLightColor(Vector3 _color);
    void SetAmbient(Vector3 _ambient);
    void SetDiffuse(Vector3 _diffuse);
    void SetSpecular(Vector3 _specular);
    void SetRange(float _range);
    float GetRange() const;
    Vector3 GetLightColor() const;
    Vector3 GetAmbient() const;
    Vector3 GetDiffuse() const;
    Vector3 GetSpecular() const;
    Light(Renderer* _renderer);
    ~Light();
};

