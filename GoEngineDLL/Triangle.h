#pragma once
#include "Shape.h"

class Triangle :
	public Shape {
public:
	void Draw() override;
	Triangle(Renderer* _renderer);
	virtual ~Triangle();
};

