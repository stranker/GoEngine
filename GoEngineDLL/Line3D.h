#pragma once
#include "Entity3D.h"

class ENGINEDLL_API Line3D :
    public Entity3D {
private:
    Material* lineMaterial;
    Vector3 startPoint;
    Vector3 endPoint;
    Color lineColor;
public:
    void Draw() override;
    void CreateLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor);
    void SetMaterial(Material* material);
    Line3D();
    ~Line3D();
};

