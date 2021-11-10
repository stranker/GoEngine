#include "Light.h"

void Light::Draw() {
    if (!CanBeDrawed()) { return Node3D::Draw(); }
    if (spatialMaterial) {
        spatialMaterial->Use();
        spatialMaterial->GetShader()->SetVec3("lightColor", lightColor);
        spatialMaterial->GetShader()->SetMat4("model", globalTransform->GetTransform());
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, true);
    Primitive::Draw();
}

void Light::SetLightColor(Vector3 _color) {
    lightColor = _color;
}

void Light::SetSpecular(float _specular) {
    specular = _specular;
    specular = Utils::Clamp(specular, 0, 1);
}

void Light::SetEnergy(float _energy) {
    energy = _energy;
    energy = Utils::Clamp(energy, 0, 16);
}

void Light::ShowUI() {
    Node3D::ShowUI();
    UILayer::ShowLightInfo(this);
}

Vector3 Light::GetLightColor() const {
    return lightColor;
}

float Light::GetSpecular() const {
    return specular;
}

float Light::GetEnergy() const {
    return energy;
}

Renderer::LightType Light::GetType() const {
    return type;
}

Light::Light(Vector3 _color, float _energy, float _specular) : Light(){
    lightColor = _color;
    energy = _energy;
    specular = _specular;
}

Light::Light() : Sphere() {
    SetDefaultName("Light");
    spatialMaterial = ResourceManager::LoadSpatialMaterial("Shaders/SpatialMaterial.vs", "Shaders/LightCube.fs", "lightMaterial");
}

Light::~Light() {
}

DirectionalLight::DirectionalLight(Vector3 _color, float _energy, float _specular) : Light(_color, _energy, _specular) {
    SetDefaultName("DirectionalLight");
    type = Renderer::DIRECTIONAL;
    Renderer::GetSingleton()->AddLight(this);
}

DirectionalLight::DirectionalLight() : DirectionalLight(Vector3().One(), 1.0f, 0.5f) {
}

DirectionalLight::~DirectionalLight() {
}

PointLight::PointLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 _attenuation) : Light(_color, _energy, _specular){
    SetDefaultName("PointLight");
    type = Renderer::POINT;
    kConstant = _attenuation.x;
    kLinear = _attenuation.y;
    kQuadratic = _attenuation.z;
    range = _range;
    Renderer::GetSingleton()->AddLight(this);
}

PointLight::PointLight() : PointLight(Vector3().One(), 1.0f, 0.5f, 1.0f, Vector3(1.0f,0.7f,1.8f)) {
}

PointLight::~PointLight() {
}

SpotLight::SpotLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 _attenuation, float _cutOff, float _outerCutOff) :
    PointLight(_color, _energy, _specular, _range, _attenuation) {
    SetDefaultName("SpotLight");
    type = Renderer::SPOT;
    cutOff = _cutOff;
    outerCutOff = _outerCutOff;
    Renderer::GetSingleton()->AddLight(this);
}

SpotLight::SpotLight() : SpotLight(Vector3().One(), 1.0f, 0.5f, 1.0f, Vector3(0.7f, 1.8f, 1.0f),glm::cos(glm::radians(45.0f)), glm::cos(glm::radians(1.0f)))
{
}

SpotLight::~SpotLight() {
}
