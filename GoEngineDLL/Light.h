#pragma once
#include "Primitive.h"

class ENGINEDLL_API Light :
    public Primitive {
protected:
    Renderer::LightType type;
    Vector3 lightColor;
    float energy;
    float specular;
    const int drawVertices = 12 * 3;
private:

public:
    void Draw() override;
    void SetLightColor(Vector3 _color);
    void SetSpecular(float _specular);
    void SetEnergy(float _energy);
    Vector3 GetLightColor() const;
    float GetSpecular() const;
    float GetEnergy() const;
    Renderer::LightType GetType() const;
    Light(Vector3 _color, float _energy, float _specular);
    Light();
    ~Light();

};

class ENGINEDLL_API DirectionalLight : 
    public Light {
protected:
    Vector3 direction;
public:
    Vector3 GetDirection() const { return direction; };
    DirectionalLight(Vector3 _color, float _energy, float _specular, Vector3 _direction);
    DirectionalLight();
    ~DirectionalLight();
};

class ENGINEDLL_API PointLight :
    public Light {
protected:
    float range;
    float kConstant;
    float kLinear;
    float kQuadratic;
public:
    float GetRange() const { return range; };
    Vector3 GetAttenuation() const { return Vector3(kConstant, kLinear, kQuadratic); };
    PointLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 _attenuation);
    PointLight();
    ~PointLight();
};

class ENGINEDLL_API SpotLight :
    public PointLight {
protected:
    float cutOff;
    float outerCutOff;
    Vector3 direction;
public:
    Vector3 GetDirection() const { return direction; };
    float GetCutOff() const { return cutOff; };
    float GetOuterCutOff() const { return outerCutOff; };
    SpotLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 direction, Vector3 _attenuation, float _cutOff, float _outerCutOff);
    SpotLight();
    ~SpotLight();
};
