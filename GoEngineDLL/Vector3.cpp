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

Vector3 Vector3::Cross(Vector3 vec2){
	x = y * vec2.z - (vec2.y * z);
	y = -(x * vec2.z - (vec2.x * z));
	z = x * vec2.y - (vec2.x * y);
	return Vector3(x, y, z);
}

float Vector3::Dot(Vector3 vec2){
	return (x * vec2.x) + (y * vec2.y) + (z * vec2.z);
}

Vector3 Vector3::Zero() {
	return Vector3(0, 0, 0);
}

Vector3 Vector3::One() {
	return Vector3(1, 1, 1);
}

Vector3	Vector3::Up(){
	return Vector3(0, 1, 0);
}

Vector3	Vector3::Down(){
	return Vector3(0, -1, 0);
}

Vector3	Vector3::Foward(){
	return Vector3(0, 0, -1);
}

Vector3	Vector3::Back(){
	return Vector3(0, 0, 1);
}

Vector3 Vector3::Right(){
	return Vector3(1, 0, 0);
}

Vector3 Vector3::Left(){
	return Vector3(-1, 0, 0);
}

string Vector3::ToString() {
	string output = "Vector3(" + to_string(x) + "," + to_string(y) +  "," + to_string(z) + ")";
	return output;
}

Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}
