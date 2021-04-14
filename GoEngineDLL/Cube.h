#pragma once
#include "Primitive.h"
#include "Light.h"

class ENGINEDLL_API Cube : 
	public Primitive {
private:
	const int drawVertices = 12*3;
	Light* light;
public:
	void SetLight(Light* _light);
	void Draw() override;
	Cube(Renderer* _renderer);
	~Cube();
};

