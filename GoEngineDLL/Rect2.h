#pragma once
#include "Exports.h"
#include "Vector2.h"

struct ENGINEDLL_API Rect2 {
	float x;
	float y;
	float width;
	float height;

	Rect2() { x = 0; y = 0; width = 0; height = 0; };
	Rect2(float _x, float _y, float w, float h);
	Rect2(Vector2 pos, Vector2 size);
	float Dot(const Rect2& rec) const;
};

