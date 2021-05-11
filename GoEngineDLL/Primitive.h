#pragma once
#include "VisualInstance3D.h"
#include "SpatialMaterial.h"

class ENGINEDLL_API Primitive :
    public VisualInstance3D {
protected:
    SpatialMaterial* spatialMaterial;
public:
    void SetMaterial(SpatialMaterial* spatialMaterial);
    void Destroy() override;
    Primitive();
    ~Primitive();
};

