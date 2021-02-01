#pragma once
#include "Entity2D.h"

class ENGINEDLL_API Shape :
	public Entity2D {
protected:
	Material *material;
public:
	virtual void Draw() = 0;
	virtual void Destroy() = 0;
	Shape(Renderer* _renderer);
	~Shape();
};

