#pragma once
#include <BaseGame.h>

class TankBullet :
    public Node3D {
private:
    Vector3 velocity;
    Vector3 direction;
    float speed = 30;
    Node3D* model;
public:
    void SetDirection(Vector3 dir);
    void Ready();
    void Update(float deltaTime);
    TankBullet();
};

