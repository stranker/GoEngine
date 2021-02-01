#pragma once
#include <iostream>
#include "Exports.h"

using namespace std;

struct ENGINEDLL_API Vector3 {
	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3 &vec) const;
	Vector3 operator-(const Vector3 &vec) const;
	bool operator==(const Vector3 &vec) const;
	Vector3 operator*(const float k) const;
	Vector3 operator/(const float k) const;
	Vector3 Normalize();
	Vector3 Zero();
	Vector3 One();
	Vector3() {};
	Vector3(float _x, float _y, float _z);
};