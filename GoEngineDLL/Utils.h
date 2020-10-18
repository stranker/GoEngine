#pragma once
#include <algorithm>

using namespace std;

class Utils {
public:
	static float Clamp(float value, float min_value, float max_value);
	Utils();
	~Utils();
};

