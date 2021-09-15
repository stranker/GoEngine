#include "Quad.h"

void Quad::Draw() {
    if (!IsInsideFrustum()) {
        return Node3D::Draw();
    }
    if (spatialMaterial) {
        spatialMaterial->Use(); // Uso el material
        spatialMaterial->SetMat4("model", globalTransform->GetTransform());
        spatialMaterial->SetMat4("view", Renderer::GetSingleton()->GetCamera()->GetView());
        spatialMaterial->SetMat4("projection", Renderer::GetSingleton()->GetCamera()->GetProjection());
        spatialMaterial->SetVec3("viewPos", Renderer::GetSingleton()->GetCameraTransform()->GetPosition());
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, true);
    spatialMaterial->ResetTextureActive();
    Node3D::Draw();
}

void Quad::UpdateQuad(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) {
    float position_vertex_data[] = {
        v1.x, v1.y, v1.z,
        v2.x, v2.y, v2.z,
        v3.x, v3.y, v3.z,
        v4.x, v4.y, v4.z,
    };
    UpdateVertexData(position_vertex_data, sizeof(position_vertex_data), 0);
}

Quad::Quad() : Primitive() {
	SetDefaultName("Quad");
    className = "Quad";
    float position_vertex_data[] = {
    -0.5f, 0.5f, 0.f,
    -0.5f,-0.5f, 0.f,
     0.5f,-0.5f, 0.f,
     0.5f, 0.5f, 0.f
    };
    float normal_vertex_data[] = {
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f,
     0.0f,  0.0f, -1.0f
    };
    float uv_vertex_data[] = {
     0.0f,  1.0f,
     0.0f,  0.0f,
     1.0f,  0.0f,
     1.0f,  1.0f
    };
    int indices_vertex_data[] = {
     0, 1, 2,
     2, 3, 0
    };
    CreateVertexArrayID(); //crea el VAO
    BindVertexArray();
    CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0); // VBO
    CreateVertexData(normal_vertex_data, sizeof(normal_vertex_data), 3, Renderer::ARRAY_BUFFER, 1); // VBO
    CreateVertexData(uv_vertex_data, sizeof(uv_vertex_data), 2, Renderer::ARRAY_BUFFER, 2); // VBO
    CreateVertexData(indices_vertex_data, sizeof(indices_vertex_data), 1, Renderer::ELEMENT_BUFFER, -1); // VBO
    BindVertexObjects(); // Bindeo VAO
    CreateBBox(position_vertex_data, 4);
    primitive = Renderer::TRIANGLES;
}

Quad::~Quad() {
}

Plane BSPQuad::GetPlane() {
    float d = GetNormal().Dot(globalTransform->GetPosition());
    return Plane(GetNormal(), d);
}

Vector3 BSPQuad::GetNormal() {
    return transform->GetFoward();
}

BSPQuad::BSPQuad() : Quad() {
    className = "BSPQuad";
    //BSP::AddPartitionPlane(this);
}

BSPQuad::BSPQuad(const string& _name) : BSPQuad() {
    SetDefaultName(_name);
}

BSPQuad::~BSPQuad() {
}
