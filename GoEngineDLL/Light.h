#pragma once
#include "Primitive.h"
class ENGINEDLL_API Light :
    public Primitive {
private:
    const int drawVertices = 12 * 3;
public:
    void Draw() override;
    Light(Renderer* _renderer);
    ~Light();
};

