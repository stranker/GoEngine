#pragma once
#include "Exports.h"
#include "Utils.h"
#include "GlInclude.h"
#include "Transform.h"

class Camera3D;

struct ENGINEDLL_API CameraFrustum {
	vector<Plane> planes;
	vector<Plane> GetPlanes();
	Vector3 frustumCorners[8];
	bool IsBBoxInside(const Transform& transform, const BoundingBox& bbox);
	bool IsBBoxInside(const BoundingBox& bbox);
	bool IsPointInside(const Vector3& point);
	void CalculateFrustum(Camera3D* camera);
};

