#pragma once
#include "Primitive.h"
#include "Light.h"

class ENGINEDLL_API Cube : 
	public Primitive {
private:
	Light* light;
	const int LIGHT_SHADER_VERSION = 2;
	const int drawVertices = 36;
public:
	void SetMaterial(SpatialMaterial* spatialMaterial);
	void SetLight(Light* light);
	void Draw() override;
	Cube(Renderer* _renderer);
	~Cube();
};

