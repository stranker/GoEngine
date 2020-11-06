#pragma once
#include <iostream>
#include "Exports.h"
#include "glm/glm.hpp"

using namespace std;

struct ENGINEDLL_API Vector2 {
	float x;
	float y;

	Vector2 operator+(const Vector2 &vec) const;
	Vector2 operator-(const Vector2 &vec) const;
	bool operator==(const Vector2 &vec) const;
	Vector2 operator*(const float k) const;
	Vector2 operator/(const float k) const;
	Vector2 operator-=(const Vector2 &vec) const;
	Vector2 Normalize();
	Vector2 Zero();
	Vector2 One();
	Vector2 Up();
	Vector2 Down();
	Vector2 Right();
	Vector2 Left();
	float Angle();
	Vector2() {};
	Vector2(float x, float y);
};