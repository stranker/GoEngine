#pragma once
#include <iostream>
#include <string>
#include "Exports.h"
#include "glm/glm.hpp"

using namespace std;

struct ENGINEDLL_API Vector2 {
	float x = 0;
	float y = 0;

	Vector2 operator+(const Vector2 &vec) const;
	Vector2 operator-(const Vector2 &vec) const;
	bool operator==(const Vector2 &vec) const;
	Vector2 operator*(const float k) const;
	Vector2 operator/(const float k) const;
	Vector2 operator-=(const Vector2 &vec) const;
	float Dot(const Vector2 vec2);
	Vector2 Cross(const Vector2 vec2);
	Vector2 Normalize();
	Vector2 Zero();
	Vector2 One();
	Vector2 Up();
	Vector2 Down();
	Vector2 Right();
	Vector2 Left();
	float Angle();
	float Lenght();
	string ToString();
	Vector2() {};
	Vector2(float x, float y);
};

