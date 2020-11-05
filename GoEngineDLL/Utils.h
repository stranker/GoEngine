#pragma once
#include <algorithm>
#include "Exports.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Rect2.h"
#include "Color.h"

using namespace std;

class ENGINEDLL_API Utils {
public:
	static float Clamp(float value, float min_value, float max_value);
};

