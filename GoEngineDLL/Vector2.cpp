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

Vector2 Vector2::operator-=(const Vector2 & vec) const {
	float dx = x;
	float dy = y;
	dx -= vec.x;
	dy -= vec.y;
	return Vector2(dx, dy);
}

float Vector2::Dot(const Vector2 vec2) {
	return x * vec2.x + y * vec2.y;
}

Vector2 Vector2::Cross(const Vector2 vec2) {
	return Vector2().One() * (x * vec2.y - (y * vec2.x));
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

Vector2 Vector2::Up() {
	return Vector2(0, 1);
}

Vector2 Vector2::Down() {
	return Vector2(0, -1);
}

Vector2 Vector2::Right() {
	return Vector2(1, 0);
}

Vector2 Vector2::Left() {
	return Vector2(-1, 0);
}

float Vector2::Angle() {
	return glm::atan(y, x);
}

float Vector2::Lenght() {
	return sqrt(x * x + y * y);
}

string Vector2::ToString() {
	string output = "Vector2(" + to_string(x) + "," + to_string(y) + ")";
	return output;
}

Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}
