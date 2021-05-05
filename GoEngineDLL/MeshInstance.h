#pragma once
#include "Primitive.h"
#include "Mesh.h"

class ENGINEDLL_API MeshInstance :
    public Primitive {
protected:
    Mesh mesh;
public:
    void Draw() override;
    void Destroy() override;
    MeshInstance(string const &meshPath);
    ~MeshInstance();
};

