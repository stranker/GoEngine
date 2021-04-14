#include "Light.h"

void Light::CreateLight(Vector3 _color, Vector3 _ambient, Vector3 _diffuse, Vector3 _specular) {
    lightColor = _color;
    ambient = _ambient;
    diffuse = _diffuse;
    specular = _specular;
}

void Light::Draw() {
    if (material){
        material->Use();
        material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
        material->SetVec3("lightColor", lightColor);
    }
    renderer->Draw(GetVertexArrayID(), primitive, drawVertices, false);
    DrawGizmo();
}

void Light::SetLightColor(Vector3 _color) {
    lightColor = _color;
}

void Light::SetAmbient(Vector3 _ambient) {
    ambient = _ambient;
}

void Light::SetDiffuse(Vector3 _diffuse) {
    diffuse = _diffuse;
}

void Light::SetSpecular(Vector3 _specular) {
    specular = _specular;
}

Vector3 Light::GetLightColor() const {
    return lightColor;
}

Vector3 Light::GetAmbient() const {
    return ambient;
}

Vector3 Light::GetDiffuse() const {
    return diffuse;
}

Vector3 Light::GetSpecular() const {
    return specular;
}

Light::Light(Renderer* _renderer) : Primitive(_renderer){
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
    CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0); // VBO
    BindVertexObjects(); // Bindeo VAO
    primitive = Renderer::TRIANGLES;
    material = new Material();
    material->LoadShaders("Shaders/SimpleVertex3dShader.shader", "Shaders/LightCubeFragmentShader.shader");
    cout << "Creating Light" << endl;
}

Light::~Light() {
}
