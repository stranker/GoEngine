#pragma once
#include "Entity3D.h"

class ENGINEDLL_API Cube : 
	public Entity3D {
private:
	const int drawVertices = 12*3;
public:
	void Draw() override;
	Cube(Renderer* _renderer);
	~Cube();
};

