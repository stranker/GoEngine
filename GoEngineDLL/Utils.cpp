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

bool Utils::Within(float min, float value, float max) {
	return value >= min && value <= max;
}

float Utils::Max(float v1, float v2) {
	return v1 > v2 ? v1 : v2;
}

float Utils::Min(float v1, float v2) {
	return v1 < v2 ? v1 : v2;
}

Vector3 Utils::IntersectPlanes(const Plane& p1, const Plane& p2, const Plane& p3) {
	Vector3 m1 = Vector3(p1.a, p2.a, p3.a);
	Vector3 m2 = Vector3(p1.b, p2.b, p3.b);
	Vector3 m3 = Vector3(p1.c, p2.c, p3.c);
	Vector3 d = Vector3(p1.d, p2.d, p3.d);

	Vector3 u = m2.Cross(m3);
	Vector3 v = m1.Cross(d);

	float denom = m1.Dot(u);

	if (glm::abs(denom) < 0.00001) {
		return Vector3(0, 0, 0);
	}
	return Vector3(d.Dot(u) / denom, m3.Dot(v) / denom, -(m2.Dot(v)) / denom);
}


AABB::AABB(Rect2 rect) {
	min = Vector2(rect.x, rect.y);
	max = min + Vector2(rect.width, rect.height);
}

AABB::AABB(Vector2 pos, Vector2 size) {
	min = Vector2(pos.x, pos.y);
	max = min + Vector2(size.x, size.y);
}

void BoundingBox::GenerateCorners() {
	corners.clear();
	corners = {
		{Vector3(min.x, min.y, min.z)}, // x y z
		{Vector3(max.x, min.y, min.z)}, // X y z
		{Vector3(min.x, max.y, min.z)}, // x Y z
		{Vector3(max.x, max.y, min.z)}, // X Y z

		{Vector3(min.x, min.y, max.z)}, // x y Z
		{Vector3(max.x, min.y, max.z)}, // X y Z
		{Vector3(min.x, max.y, max.z)}, // x Y Z
		{Vector3(max.x, max.y, max.z)}, // X Y Z
	};
}

bool BoundingBox::operator!=(const BoundingBox& bbox) const {
	return min != bbox.min && max != bbox.max;
}

bool BoundingBox::operator==(const BoundingBox& bbox) const {
	return min == bbox.min && max == bbox.max;
}

BoundingBox BoundingBox::operator*(Vector3 vec) const{
	BoundingBox bb;
	bb.min = vec.Cross(min);
	bb.max = vec.Cross(max);
	return bb;
}

BoundingBox::BoundingBox(Vector3 _min, Vector3 _max) {
	min = _min;
	max = _max;
	GenerateCorners();
}

BoundingBox::BoundingBox(const BoundingBox& bb1, const BoundingBox& bb2) {
	Vector3 minA1 = bb1.min;
	Vector3 minA2 = bb2.min;
	min.x = Utils::Min(minA1.x, minA2.x);
	min.y = Utils::Min(minA1.y, minA2.y);
	min.z = Utils::Min(minA1.z, minA2.z);

	Vector3 maxA1 = bb1.max;
	Vector3 maxA2 = bb2.max;
	max.x = Utils::Max(maxA1.x, maxA2.x);
	max.y = Utils::Max(maxA1.y, maxA2.y);
	max.z = Utils::Max(maxA1.z, maxA2.z);
	GenerateCorners();
}

BoundingBox::BoundingBox() {
	min = Vector3();
	max = Vector3();
	GenerateCorners();
}

void Plane::Normalize() {
	double mag;
	mag = sqrt(a * a + b * b + c * c);
	if (mag > 0) {
		a = a / mag;
		b = b / mag;
		c = c / mag;
		d = d / mag;
	}
}

float Plane::DistanceToPoint(const Vector3& point) {
	return a * point.x + b * point.y + c * point.z + d;
}

Plane::Halfspace Plane::ClassifyPoint(const Vector3& point) {
	float dist;
	dist = DistanceToPoint(point);
	if (dist < 0) return Plane::NEGATIVE;
	if (dist > 0) return Plane::POSITIVE;
	return Plane::ON_PLANE;
}

Vector3 Plane::Normal() {
	return Vector3(a, b, c);
}

Plane::Plane() {
	a = 0;
	b = 0;
	c = 0;
	d = 0;
}

Plane::Plane(const Vector3& normal, float _d) {
	a = normal.x;
	b = normal.y;
	c = normal.z;
	d = _d;
}

Plane::Plane(float _a, float _b, float _c, float _d) {
	a = _a;
	b = _b;
	c = _c;
	d = _d;
}

Plane::Plane(const Vector3& vA, const Vector3& vB, const Vector3& vC) {
	Vector3 n = ((vB - vA).Cross(vC - vA)).Normalize();
	float nd = n.Dot(vA);
	a = n.x;
	b = n.y;
	c = n.z;
	d = nd;
}
