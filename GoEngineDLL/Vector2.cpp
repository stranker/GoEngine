#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2 & vec) const {
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2 & vec) const {
	return Vector2(x - vec.x, y - vec.y);
}

bool Vector2::operator==(const Vector2 & vec) const {
	return x == vec.x && y == vec.y;
}

Vector2 Vector2::operator*(const float k) const {
	return Vector2(x * k, y * k);
}

Vector2 Vector2::operator/(const float k) const {
	return Vector2(x / k, y / k);
}

Vector2 Vector2::Normalize() {
	float mod = sqrt(x * x + y * y);
	if (mod != 0) {
		x /= mod;
		y /= mod;
	}
	return Vector2(x, y);
}

Vector2 Vector2::Zero() {
	return Vector2(0, 0);
}

Vector2 Vector2::One() {
	return Vector2(1, 1);
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}
