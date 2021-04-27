#pragma once
#include "Entity3D.h"
class ENGINEDLL_API Mesh :
    public Entity3D {
private:
    void SetupMesh();
public:
    // mesh data
    vector<Vector3> vertices;
    vector<unsigned int> indices;

    Mesh();
    void Draw() override;
};

