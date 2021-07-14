#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <string.h>
#include "Exports.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Rect2.h"
#include "Color.h"

#define PI 3.14159265

#define PRINT_DEBUG(x) cout << x << endl;

using namespace std;

struct AABB {
	Vector2 min;
	Vector2 max;

	AABB(Rect2 rect);
	AABB(Vector2 pos, Vector2 size);
};

struct BoundingBox {
	Vector3 min;
	Vector3 max;
	vector<Vector3> corners;
	BoundingBox(Vector3 _min, Vector3 _max);
	BoundingBox(const BoundingBox& bb1, const BoundingBox& bb2);
	bool operator!=(const BoundingBox& bbox) const;
	bool operator==(const BoundingBox& bbox) const;
	BoundingBox operator*(Vector3 vec) const;
	void GenerateCorners();
	BoundingBox();
};

struct Plane {
	float a;
	float b;
	float c;
	float d;
	enum Halfspace {
		NEGATIVE = -1,
		ON_PLANE = 0,
		POSITIVE = 1
	};
	void Normalize();
	float DistanceToPoint(const Vector3& point);
	Halfspace ClassifyPoint(const Vector3& point);
	Vector3 Normal();
	Plane(const Vector3& vA, const Vector3& vB, const Vector3& vC);
	Plane();
	Plane(const Vector3& normal, float _d);
	Plane(float _a, float _b, float _c, float _d);
};

class ENGINEDLL_API Utils {
public:
	static float Clamp(float value, float min_value, float max_value);
	static float RadToDeg(float value);
	static float DegToRad(float value);
	static float RandRange(float minValue, float maxValue);
	static bool Within(float min, float value, float max);
	static float Max(float v1, float v2);
	static float Min(float v1, float v2);
	static Vector3 IntersectPlanes(const Plane& p1, const Plane& p2, const Plane& p3);
};

