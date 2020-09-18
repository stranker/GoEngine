#pragma once
#include "Shape.h"
class Square :
	public Shape {
public:
	void Draw() override;
	Square(Renderer *_renderer);
	virtual ~Square();
};

