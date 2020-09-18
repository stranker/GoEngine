#pragma once
#include "Entity2D.h"
class Shape :
	public Entity2D
{
protected:
	Renderer::Primitive primitive;
public:
	virtual void Draw() = 0;
	Shape(Renderer* _renderer);
	~Shape();
};

