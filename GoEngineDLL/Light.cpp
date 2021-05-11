#include "Light.h"

void Light::Draw() {
    if (spatialMaterial){
        spatialMaterial->Use();
        spatialMaterial->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(transform->GetTransform()));
        spatialMaterial->SetVec3("lightColor", lightColor);
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, false);
    DrawGizmo();
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
    energy = Utils::Clamp(energy, 0, 10);
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

Light::Light() {
    float position_vertex_data[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    CreateVertexArrayID(); //crea el VAO
    BindVertexArray();
    CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0); // VBO
    BindVertexObjects(); // Bindeo VAO
    primitive = Renderer::TRIANGLES;
    spatialMaterial = new SpatialMaterial();
    spatialMaterial->LoadShaders("Shaders/Simple3D.vs", "Shaders/LightCube.fs");
}

Light::~Light() {
}

DirectionalLight::DirectionalLight(Vector3 _color, float _energy, float _specular, Vector3 _direction) : Light(_color, _energy, _specular) {
    type = Renderer::DIRECTIONAL;
    direction = _direction;
}

DirectionalLight::DirectionalLight() {
    type = Renderer::DIRECTIONAL;
    lightColor = Vector3().One();
    energy = 1.0f;
    specular = 0.5f;
    direction = GetTransform()->GetFoward();
}

DirectionalLight::~DirectionalLight() {
}

PointLight::PointLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 _attenuation) : Light(_color, _energy, _specular){
    type = Renderer::POINT;
    kConstant = _attenuation.x;
    kLinear = _attenuation.y;
    kQuadratic = _attenuation.z;
    range = _range;
}

PointLight::PointLight() {
    type = Renderer::POINT;
    lightColor = Vector3().One();
    energy = 1.0f;
    specular = 0.5f;
    kConstant = 1.0f;
    kLinear = 0.7f;
    kQuadratic = 1.8f;
    range = 1.0f;
}

PointLight::~PointLight() {
}

SpotLight::SpotLight(Vector3 _color, float _energy, float _specular, float _range, Vector3 _direction, Vector3 _attenuation, float _cutOff, float _outerCutOff) :
    PointLight(_color, _energy, _specular, _range, _attenuation) {
    type = Renderer::SPOT;
    cutOff = glm::cos(glm::radians(_cutOff));
    outerCutOff = glm::cos(glm::radians(_outerCutOff));
    direction = _direction;
}

SpotLight::SpotLight() {
    type = Renderer::SPOT;
    lightColor = Vector3().One();
    direction = GetTransform()->GetFoward();
    energy = 1.0f;
    specular = 0.5f;
    kConstant = 1.0f;
    kLinear = 0.7f;
    kQuadratic = 1.8f;
    range = 1.0f;
    cutOff = glm::cos(glm::radians(45.0f));
    outerCutOff = glm::cos(glm::radians(1.0f));
}

SpotLight::~SpotLight() {
}
