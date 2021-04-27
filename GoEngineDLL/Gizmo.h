#pragma once
#include "Line3D.h"

class ENGINEDLL_API Gizmo :
    public Line3D {
private:
    Material* lineMaterial;
    Line3D* redLine;
    Line3D* blueLine;
    Line3D* greenLine;
public:
    void SetPosition(Vector3 position);
    void Translate(Vector3 position);
    void Rotate(Vector3  rotation);
    void Rotate(float angle, Vector3 axis);
    void Draw() override;
    void Destroy() override;
    Gizmo();
    ~Gizmo();
};

