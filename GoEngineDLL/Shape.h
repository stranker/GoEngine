#pragma once
#include "Entity2D.h"
class Shape :
	public Entity2D
{
public:
	GLuint CreateTriangleBuffer();
	Shape();
	~Shape();
};

