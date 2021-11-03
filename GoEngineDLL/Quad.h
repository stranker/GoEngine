#pragma once
#include "Primitive.h"

class ENGINEDLL_API Quad :
    public Primitive {
protected:
    SpatialMaterial* nextPassMaterial;
public:
    virtual void Draw() override;
    virtual void ForceDraw(SpatialMaterial * material) override;
    void UpdateQuad(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4);
    Quad();
    ~Quad();
};

class ENGINEDLL_API BSPQuad : public Quad {
public:
    Plane GetPlane();
    Vector3 GetNormal();
    BSPQuad();
    BSPQuad(const string& name);
    ~BSPQuad();
};
