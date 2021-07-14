#pragma once
#include <BaseGame.h>

class Mine :
    public Node3D {
private:
    Node3D* model;
    bool exploted;
public:
    Mine();
};

