#pragma once
#include "Primitive.h"

class ENGINEDLL_API Line3D : public Primitive{
private:
    Vector3 startPoint;
    Vector3 endPoint;
    Color lineColor;
public:
    void Draw(Transform* transform);
    void CreateLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor);
    void SetLine(Vector3 _startPoint, Vector3 _endPoint);
    void SetLine(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor);
    Line3D(Vector3 _startPoint, Vector3 _endPoint, Color _lineColor);
    Line3D();
};
