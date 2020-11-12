#pragma once
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "Exports.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Rect2.h"
#include "Color.h"

#define PI 3.14159265

using namespace std;

struct AABB {
	Vector2 min;
	Vector2 max;

	AABB(Rect2 rect);
	AABB(Vector2 pos, Vector2 size);
};

class ENGINEDLL_API Utils {
public:
	static float Clamp(float value, float min_value, float max_value);
	static float RadToDeg(float value);
	static float DegToRad(float value);
};

