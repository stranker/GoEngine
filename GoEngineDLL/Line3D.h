#pragma once
#include "Entity3D.h"
class ENGINEDLL_API Line3D :
    public Entity3D {
private:
    Vector3 startPoint;
    Vector3 endPoint;
    Color lineColor;
public:
    void Draw() override;
    void CreateLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor);
    Line3D(Renderer* _renderer);
    ~Line3D();
};

