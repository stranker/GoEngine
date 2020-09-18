#pragma once
#include "Shape.h"

class ENGINEDLL_API Square :
	public Shape {
public:
	void Draw() override;
	Square(Renderer *_renderer);
	virtual ~Square();
};

