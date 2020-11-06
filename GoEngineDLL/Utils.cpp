#include "Utils.h"

float Utils::Clamp(float value, float min_value, float max_value) {
	float new_value = value;
	if (new_value < min_value) {
		new_value = min_value;
	}
	else if (new_value > max_value) {
		new_value = max_value;
	}
	return new_value;
}

float Utils::RadToDeg(float value) {
	return value * (180.0f / PI);
}

float Utils::DegToRad(float value) {
	return value * (PI / 180.0f);
}
