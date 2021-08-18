#pragma once
#include "VisualInstance3D.h"
#include "SpatialMaterial.h"

class ENGINEDLL_API Primitive :
    public VisualInstance3D {
protected:
    SpatialMaterial* spatialMaterial;
    SpatialMaterial* defaultMaterial;
public:
    void SetMaterial(SpatialMaterial* spatialMaterial);
    void Draw() override;
    Primitive();
};

