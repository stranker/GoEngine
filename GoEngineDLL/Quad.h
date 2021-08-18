#pragma once
#include "Primitive.h"

class ENGINEDLL_API Quad :
    public Primitive {
private:
    const int drawVertices = 6;
public:
    virtual void Draw() override;
    Quad();
    ~Quad();
};

