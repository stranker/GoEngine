#pragma once
#include "Primitive.h"
#include "Light.h"

class ENGINEDLL_API Cube : 
	public Primitive {
private:
	const int drawVertices = 36;
public:
	void SetMaterial(SpatialMaterial* spatialMaterial);
	void Draw() override;
	Cube();
	~Cube();
};

