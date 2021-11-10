#pragma once
#include "Sphere.h"

class ENGINEDLL_API Light :
    public Sphere {
protected:
    Renderer::LightType type;
    Vector3 lightColor;
    float energy = 0;
    float specular = 0.5f;
public:
    void Draw() override;
    void SetLightColor(Vector3 _color);
    void SetSpecular(float _specular);
    void SetEnergy(float _energy);
    virtual void ShowUI() override;
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
public:
    DirectionalLight(Vector3 _color, float _energy, float _specular);
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
    void SetRange(float _range) { range = _range;};
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
public:
    float GetCutOff() const { return cutOff; };
    float GetOuterCutOff() const { return outerCutOff; };
    void SetCutOff(float _cutOff) { cutOff = _cutOff;};
    void SetOuterCutOff(float _outerCutOff) { outerCutOff = _outerCutOff; };
    SpotLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 _attenuation, float _cutOff, float _outerCutOff);
    SpotLight();
    ~SpotLight();
};
