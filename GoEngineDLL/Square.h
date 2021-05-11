#pragma once
#include "Shape.h"

class ENGINEDLL_API Square :
	public Shape {
private:
	const int draw_vertices = 6;
public:
	void Draw() override;
	Square();
	virtual ~Square();
};

