#pragma once
#include "Exports.h"

struct ENGINEDLL_API Color {
	float a;
	float r;
	float g;
	float b;

	Color();
	Color(float _r, float _g, float _b, float _a);
	Color(float _r, float _g, float _b);
	Color Blue() const;
	Color Red() const;
	Color Green() const;
	Color Yellow() const;
	Color Black() const;
	Color Cyan() const;
	Color Magenta() const;
	Color Purple() const;
};
