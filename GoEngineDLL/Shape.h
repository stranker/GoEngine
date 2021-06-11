#pragma once
#include "Node2D.h"

class ENGINEDLL_API Shape :
	public Node2D {
protected:
	Material *material;
public:
	virtual void Draw() = 0;
	virtual void Destroy() = 0;
	Shape();
	~Shape();
};

