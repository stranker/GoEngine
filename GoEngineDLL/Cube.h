#pragma once
#include "Primitive.h"

class ENGINEDLL_API Cube : 
	public Primitive {
private:
	const int drawVertices = 12*3;
	Vector3 lightPosition;
public:
	void SetLightPosition(Vector3 pos);
	void Draw() override;
	Cube(Renderer* _renderer);
	~Cube();
};

