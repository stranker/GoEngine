#include "Vector3.h"

Vector3 Vector3::operator+(const Vector3 & vec) const {
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3 & vec) const {
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

bool Vector3::operator==(const Vector3 & vec) const {
	return x == vec.x && y == vec.y && z == vec.z;
}

Vector3 Vector3::operator*(const float k) const {
	return Vector3(x * k, y * k, z * k);
}

Vector3 Vector3::operator/(const float k) const {
	return Vector3(x / k, y / k, z / k);
}

Vector3 Vector3::Normalize() {
	float mod = sqrt(x * x + y * y + z * z);
	if (mod != 0) {
		x /= mod;
		y /= mod;
		z /= mod;
	}
	return Vector3(x, y, z);
}

Vector3 Vector3::Zero() {
	return Vector3(0, 0, 0);
}

Vector3 Vector3::One() {
	return Vector3(1, 1, 1);
}

Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}
