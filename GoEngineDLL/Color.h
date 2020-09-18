#pragma once
#include "Exports.h"

class ENGINEDLL_API Color {
public:
	float a;
	float r;
	float g;
	float b;
	Color();
	Color(float _r, float _g, float _b, float _a);
	Color(float _r, float _g, float _b);
	Color Blue();
	Color Red();
	Color Green();
	Color Yellow();
	Color Black();
	Color Cyan();
	Color Magenta();
	Color Purple();
	virtual ~Color();
};

