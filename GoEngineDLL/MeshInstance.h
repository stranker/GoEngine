#pragma once
#include "Primitive.h"
#include "ModelImporter.h"

class ENGINEDLL_API MeshInstance :
    public Primitive {
protected:
    MeshData* mesh;
public:
    void Draw() override;
	void SetMesh(MeshData* _mesh);
    virtual Plane GetPlane() override;
    MeshInstance();
};

