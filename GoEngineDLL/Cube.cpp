#include "Cube.h"

void Cube::SetMaterial(SpatialMaterial* _spatialMaterial) {
    spatialMaterial = _spatialMaterial;
}

void Cube::SetLight(Light* _light) {
    light = _light;
}

void Cube::Draw() {
    if (spatialMaterial) {
        spatialMaterial->Use(); // Uso el material
        spatialMaterial->SetMat4("model", GetTransform()->GetTransform());
        spatialMaterial->SetMat4("view", renderer->GetCamera()->GetView());
        spatialMaterial->SetMat4("projection", renderer->GetCamera()->GetProjection());
        spatialMaterial->SetVec3("viewPos", renderer->GetCamera()->GetTransform()->GetPosition());
        
        switch (LIGHT_SHADER_VERSION){
            case 0:
                spatialMaterial->SetVec3("lightColor", light->GetLightColor());
                spatialMaterial->SetVec3("objectColor", Vector3(1.0f, 0.5f, 0.31f));
                spatialMaterial->SetVec3("lightPos", light->GetPosition());
                break;
            case 1:
                spatialMaterial->SetVec3("light.position", light->GetPosition());
                spatialMaterial->SetVec3("light.ambient", light->GetAmbient());
                spatialMaterial->SetVec3("light.diffuse", light->GetDiffuse());
                spatialMaterial->SetVec3("light.specular", light->GetSpecular());
                break;
            case 2:
                spatialMaterial->SetVec3("light.position", light->GetPosition());
                spatialMaterial->SetVec3("light.ambient", light->GetAmbient());
                spatialMaterial->SetVec3("light.diffuse", light->GetDiffuse());
                spatialMaterial->SetVec3("light.specular", light->GetSpecular());
                
                spatialMaterial->SetVec3("light.direction", light->GetTransform()->GetFoward());
                spatialMaterial->SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
                spatialMaterial->SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
                spatialMaterial->SetFloat("light.constant", 1.0f);
                spatialMaterial->SetFloat("light.linear", 0.7f);
                spatialMaterial->SetFloat("light.quadratic", 1.8f);
                spatialMaterial->SetFloat("light.range",  light->GetRange());
                break;
            case 3:
                spatialMaterial->SetVec3("light.position", light->GetPosition());
                spatialMaterial->SetVec3("light.ambient", light->GetAmbient());
                spatialMaterial->SetVec3("light.diffuse", light->GetDiffuse());
                spatialMaterial->SetVec3("light.specular", light->GetSpecular());
                break;
            default:
                break;
        }
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, false);
    DrawGizmo();
}

Cube::Cube(Renderer* _renderer) : Primitive(_renderer) {
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
    float normal_vertex_data[] = {
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,

         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,

        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,

         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,

         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,

         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
    };
    float uv_vertex_data[] = {
         1.0f,  0.0f,
         0.0f,  0.0f,
         1.0f,  1.0f,
         1.0f,  1.0f,
         0.0f,  1.0f,
         0.0f,  0.0f,

         0.0f,  0.0f,
         1.0f,  0.0f,
         1.0f,  1.0f,
         1.0f,  1.0f,
         0.0f,  1.0f,
         0.0f,  0.0f,

         1.0f,  0.0f,
         1.0f,  1.0f,
         0.0f,  1.0f,
         0.0f,  1.0f,
         0.0f,  0.0f,
         1.0f,  0.0f,

         1.0f,  0.0f,
         1.0f,  1.0f,
         0.0f,  1.0f,
         0.0f,  1.0f,
         0.0f,  0.0f,
         1.0f,  0.0f,

         0.0f,  1.0f,
         1.0f,  1.0f,
         1.0f,  0.0f,
         1.0f,  0.0f,
         0.0f,  0.0f,
         0.0f,  1.0f,

         0.0f,  1.0f,
         1.0f,  1.0f,
         1.0f,  0.0f,
         1.0f,  0.0f,
         0.0f,  0.0f,
         0.0f,  1.0f,
    };
    CreateVertexArrayID(); //crea el VAO
    CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0); // VBO
    CreateVertexData(normal_vertex_data, sizeof(normal_vertex_data), 3, Renderer::ARRAY_BUFFER, 1); // VBO
    if (LIGHT_SHADER_VERSION >= 2) {
        CreateVertexData(uv_vertex_data, sizeof(uv_vertex_data), 2, Renderer::ARRAY_BUFFER, 2); // VBO
    }
    BindVertexObjects(); // Bindeo VAO
    primitive = Renderer::TRIANGLES;
    cout << "Creating Cube" << endl;
}

Cube::~Cube() {
}