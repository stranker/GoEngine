#pragma once
#include "Primitive.h"

class ENGINEDLL_API Sphere : public Primitive {
private:
	float radius;
	unsigned int rings;
	unsigned int sectors;
	void UpdateSphere();
	void CreateSphere();
public:
	void Draw() override;
	void SetRadius(float _radius);
	Sphere();
	Sphere(float _radius, unsigned int _rings, unsigned int _sectors);
};

