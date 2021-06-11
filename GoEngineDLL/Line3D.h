#pragma once
#include "CanvasNode.h"

class ENGINEDLL_API Line3D : CanvasNode{
private:
    Material* lineMaterial;
    Vector3 startPoint;
    Vector3 endPoint;
    Color lineColor;
public:
    void Draw(const Transform& transform);
    void CreateLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor, Material* material);
    void SetMaterial(Material* material);
    Line3D();
    Line3D(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor, Material* material);
};

