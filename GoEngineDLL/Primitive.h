#pragma once
#include "Entity3D.h"
#include "Gizmo.h"

class ENGINEDLL_API Primitive :
    public Entity3D {
private:
    Gizmo* gizmo;
protected:
    void DrawGizmo();
public:
    void SetPosition(Vector3 position);
    void Translate(Vector3 position);
    void Rotate(Vector3  rotation);
    void Rotate(float angle, Vector3 axis);
    void SetScale(Vector3 scale);
    Primitive(Renderer* _renderer);
    ~Primitive();
};

