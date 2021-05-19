#pragma once
#include <iostream>
#include <string>
#include "Exports.h"

using namespace std;

struct ENGINEDLL_API Vector3 {
	float x = 0;
	float y = 0;
	float z = 0;

	Vector3 operator+(const Vector3 &vec) const;
	Vector3 operator-(const Vector3& vec) const;
	Vector3 operator+=(const Vector3 &vec);
	bool operator==(const Vector3 &vec) const;
	Vector3 operator*(const float k) const;
	Vector3 operator/(const float k) const;
	Vector3 Cross(Vector3 vec2);
	float Dot(Vector3 vec2);
	Vector3 Normalize();
	Vector3 Zero();
	Vector3 One();
	Vector3 Up();
	Vector3 Down();
	Vector3 Foward();
	Vector3 Back();
	Vector3 Right();
	Vector3 Left();
	string ToString();
	Vector3() {};
	Vector3(float _x, float _y, float _z);
};