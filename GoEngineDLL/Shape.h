#pragma once
#include "Entity2D.h"
class Shape :
	public Entity2D
{
public:
	virtual void Draw() = 0;
	Shape(Renderer* _renderer);
	~Shape();
};

