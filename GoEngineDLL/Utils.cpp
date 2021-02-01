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

float Utils::RandRange(float minValue, float maxValue) {
	return minValue + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (maxValue - minValue)));
}

AABB::AABB(Rect2 rect) {
	min = Vector2(rect.x, rect.y);
	max = min + Vector2(rect.width, rect.height);
}

AABB::AABB(Vector2 pos, Vector2 size) {
	min = Vector2(pos.x, pos.y);
	max = min + Vector2(size.x, size.y);
}
