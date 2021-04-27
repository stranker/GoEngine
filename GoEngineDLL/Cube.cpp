#include "Cube.h"

void Cube::SetMaterial(SpatialMaterial* _spatialMaterial) {
    spatialMaterial = _spatialMaterial;
}

void Cube::Draw() {
    if (spatialMaterial) {
        spatialMaterial->Use(); // Uso el material
        spatialMaterial->SetMat4("model", GetTransform()->GetTransform());
        spatialMaterial->SetMat4("view", Renderer::GetSingleton()->GetCamera()->GetView());
        spatialMaterial->SetMat4("projection", Renderer::GetSingleton()->GetCamera()->GetProjection());
        spatialMaterial->SetVec3("viewPos", Renderer::GetSingleton()->GetCamera()->GetTransform()->GetPosition());
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, false);
    DrawGizmo();
}

void Cube::SetLight(Light* l) {
    light2 = l;
}

Cube::Cube() {
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
    CreateVertexData(uv_vertex_data, sizeof(uv_vertex_data), 2, Renderer::ARRAY_BUFFER, 2); // VBO
    BindVertexObjects(); // Bindeo VAO
    primitive = Renderer::TRIANGLES;
}

Cube::~Cube() {
}