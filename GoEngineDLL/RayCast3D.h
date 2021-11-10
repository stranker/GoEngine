#pragma once
#include "Primitive.h"
#include "Line3D.h"

class ENGINEDLL_API RayCast3D :
    public Primitive {
private:
    Ray ray;
    Vector3 origin;
    Vector3 end;
    Vector3 direction;
    Color color;
    float lenght;
    Line3D* line;
    bool isColliding = false;
    Node3D* nodeColliding;
public:
    virtual void Draw() override;
    bool IsColliding() const;
    Node3D* GetCollider();
    RayCast3D();
    RayCast3D(Vector3 _origin, Vector3 _end, Color _color);
    RayCast3D(Vector3 _origin, Vector3 _dir, float _lenght, Color _color);
    ~RayCast3D() {};
};

