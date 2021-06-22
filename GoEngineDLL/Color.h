#pragma once
#include "Exports.h"
#include "Vector3.h"

struct ENGINEDLL_API Color {
	float a;
	float r;
	float g;
	float b;

	Color();
	Color(float _r, float _g, float _b, float _a);
	Color(float _r, float _g, float _b);
	Color(Vector3 vec);
	Color Red() const;
	Color Green() const;
	Color Blue() const;
	Color Yellow() const;
	Color Black() const;
	Color White() const;
	Color Cyan() const;
	Color Magenta() const;
	Color Purple() const;
	Color Interpolate(const Color& color2, float weight);
};
