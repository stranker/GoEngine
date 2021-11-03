#include "Quad.h"

void Quad::Draw() {
    if (!CanBeDrawed()) { return Node3D::Draw();}
    if (spatialMaterial) {
        spatialMaterial->Use();
        spatialMaterial->GetShader()->SetMat4("model", globalTransform->GetTransform());
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, true);
    Node3D::Draw();
}

void Quad::ForceDraw(SpatialMaterial* material) {
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, true);
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
        -1.0f, 1.0f, 0.0f,
        -1.0f,-1.0f, 0.0f,
         1.0f,-1.0f, 0.0f,
         1.0f, 1.0f, 0.0f
    };
    Vector3 normal;
    for (int i = 0; i < 4; i++) {
        int j = (i + 1) % 4;
        Vector3 vertex1 = Vector3(position_vertex_data[i * 3], position_vertex_data[i * 3 + 1], position_vertex_data[i * 3 + 2]);
        Vector3 vertex2 = Vector3(position_vertex_data[j * 3], position_vertex_data[j * 3 + 1], position_vertex_data[j * 3 + 2]);
        normal += vertex1.Cross(vertex2); // cross product
    }
    normal = normal.Normalize();
    float normal_vertex_data[] = {
        normal.x, normal.y, normal.z,
        normal.x, normal.y, normal.z,
        normal.x, normal.y, normal.z,
        normal.x, normal.y, normal.z,
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
    drawVertices = sizeof(indices_vertex_data) / sizeof(indices_vertex_data[0]);
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
