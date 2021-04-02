#pragma once
#include "Entity3D.h"
class ENGINEDLL_API Light :
    public Entity3D {
public:
    Light(Renderer* _renderer);
    ~Light();
};

