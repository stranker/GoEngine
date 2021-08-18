#pragma once
#include "Primitive.h"

class ENGINEDLL_API Cube : 
	public Primitive {
private:
	const int drawVertices = 36;
public:
	virtual void Draw() override;
	Cube();
	~Cube();
};

