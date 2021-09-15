#pragma once
#include "VisualInstance3D.h"
#include "SpatialMaterial.h"

class ENGINEDLL_API Primitive :
    public VisualInstance3D {
protected:
    SpatialMaterial* spatialMaterial;
    SpatialMaterial* defaultMaterial;
    void CreateBBox(float* data, size_t data_size);
    void CreateBBox(vector<Vector3> posData);
    bool isPartitionPlane = false;
public:
    void SetMaterial(SpatialMaterial* spatialMaterial);
    void Draw() override;
    virtual Plane GetPlane() { return Plane(); };
    void SetAsPartitionPlane(bool value);
    Primitive();
};

