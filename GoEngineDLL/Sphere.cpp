#include "Sphere.h"

inline void push_indices(vector<unsigned int>& indices, int sectors, int r, int s) {
    int curRow = r * sectors;
    int nextRow = (r + 1) * sectors;
    int nextS = (s + 1) % sectors;

    indices.push_back(curRow + s);
    indices.push_back(nextRow + s);
    indices.push_back(nextRow + nextS);

    indices.push_back(curRow + s);
    indices.push_back(nextRow + nextS);
    indices.push_back(curRow + nextS);
}

void Sphere::UpdateSphere() {
    vector<Vector3> vertexData;
    vector<Vector3> normals;
    vector<Vector2> texCoords;
    vector<unsigned int> indices;
    float const R = 1. / (float)(rings - 1);
    float const S = 1. / (float)(sectors - 1);

    for (int r = 0; r < rings; ++r) {
        for (int s = 0; s < sectors; ++s) {
            float const y = sin(-PI * 0.5 + PI * r * R);
            float const x = cos(2 * PI * s * S) * sin(PI * r * R);
            float const z = sin(2 * PI * s * S) * sin(PI * r * R);

            texCoords.push_back(Vector2(s * S, r * R));
            vertexData.push_back(Vector3(x, y, z) * radius);
            normals.push_back(Vector3(x, y, z));
            if (r < rings - 1)
                push_indices(indices, sectors, r, s);
        }
    }
    drawVertices = indices.size();
    UpdateVertexData(&vertexData[0], vertexData.size() * sizeof(float), 0);
    UpdateVertexData(&normals[0], normals.size() * sizeof(float), 1);
    UpdateVertexData(&texCoords[0], texCoords.size() * sizeof(float), 2);
    UpdateVertexData(&indices[0], indices.size() * sizeof(unsigned int), -1);
    CreateBBox(vertexData, radius);
}

void Sphere::CreateSphere() {
    vector<Vector3> vertexData;
    vector<Vector3> normals;
    vector<Vector2> texCoords;
    vector<unsigned int> indices;
    float const R = 1. / (float)(rings - 1);
    float const S = 1. / (float)(sectors - 1);

    for (int r = 0; r < rings; ++r) {
        for (int s = 0; s < sectors; ++s) {
            float const y = sin(-PI * 0.5 + PI * r * R);
            float const x = cos(2 * PI * s * S) * sin(PI * r * R);
            float const z = sin(2 * PI * s * S) * sin(PI * r * R);

            texCoords.push_back(Vector2(s * S, r * R));
            vertexData.push_back(Vector3(x, y, z) * radius);
            normals.push_back(Vector3(x,y,z));
            if (r < rings - 1)
                push_indices(indices, sectors, r, s);
        }
    }
    drawVertices = indices.size();
    CreateVertexArrayID(); //crea el VAO
    BindVertexArray();
    CreateVertexData(&vertexData[0], vertexData.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 0); // VBO
    CreateVertexData(&normals[0], normals.size() * sizeof(Vector3), 3, Renderer::ARRAY_BUFFER, 1); // VBO
    CreateVertexData(&texCoords[0], texCoords.size() * sizeof(Vector2), 2, Renderer::ARRAY_BUFFER, 2); // VBO
    CreateVertexData(&indices[0], indices.size() * sizeof(unsigned int), 1, Renderer::ELEMENT_BUFFER, -1); // VBO
    BindVertexObjects(); // Bindeo VAO
    CreateBBox(vertexData, radius);
    primitive = Renderer::TRIANGLES;
}

void Sphere::Draw() {
    if (!CanBeDrawed()) { return Node3D::Draw(); }
    if (spatialMaterial) {
        spatialMaterial->Use();
        spatialMaterial->GetShader()->SetMat4("model", globalTransform->GetTransform());
    }
    Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, drawVertices, true);
    Node3D::Draw();
}

void Sphere::SetRadius(float _radius) {
    radius = _radius;
    UpdateSphere();
}

Sphere::Sphere() {
    radius = 1;
    rings = 12;
    sectors = 24;
    CreateSphere();
}

Sphere::Sphere(float _radius, unsigned int _rings, unsigned int _sectors) {
    radius = _radius;
    rings = _rings;
    sectors = _sectors;
    CreateSphere();
}
