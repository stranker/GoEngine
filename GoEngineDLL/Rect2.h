#pragma once
#include "Exports.h"

struct ENGINEDLL_API Rect2 {
	float x;
	float y;
	float width;
	float height;

	Rect2() {};
	Rect2(float _x, float _y, float w, float h);
};

