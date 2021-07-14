#include "CameraFrustum.h"
#include "Camera3D.h"
#include "Line3D.h"

void CameraFrustum::CalculateFrustum(Camera3D* camera) {
	float proj[16];								// This will hold our projection matrix
	float modl[16];								// This will hold our modelview matrix
	float clip[16];								// This will hold the clipping planes

	const float* viewMtx = (const float*)glm::value_ptr(camera->GetTransform()->GetTransform());
	const float* projMtx = (const float*)glm::value_ptr(camera->GetProjection());
	for (size_t i = 0; i < 16; i++) {
		modl[i] = viewMtx[i];
	}
	for (size_t i = 0; i < 16; i++) {
		proj[i] = projMtx[i];
	}
	clip[0] = modl[0] * proj[0] + modl[1] * proj[4] + modl[2] * proj[8] + modl[3] * proj[12];
	clip[1] = modl[0] * proj[1] + modl[1] * proj[5] + modl[2] * proj[9] + modl[3] * proj[13];
	clip[2] = modl[0] * proj[2] + modl[1] * proj[6] + modl[2] * proj[10] + modl[3] * proj[14];
	clip[3] = modl[0] * proj[3] + modl[1] * proj[7] + modl[2] * proj[11] + modl[3] * proj[15];

	clip[4] = modl[4] * proj[0] + modl[5] * proj[4] + modl[6] * proj[8] + modl[7] * proj[12];
	clip[5] = modl[4] * proj[1] + modl[5] * proj[5] + modl[6] * proj[9] + modl[7] * proj[13];
	clip[6] = modl[4] * proj[2] + modl[5] * proj[6] + modl[6] * proj[10] + modl[7] * proj[14];
	clip[7] = modl[4] * proj[3] + modl[5] * proj[7] + modl[6] * proj[11] + modl[7] * proj[15];

	clip[8] = modl[8] * proj[0] + modl[9] * proj[4] + modl[10] * proj[8] + modl[11] * proj[12];
	clip[9] = modl[8] * proj[1] + modl[9] * proj[5] + modl[10] * proj[9] + modl[11] * proj[13];
	clip[10] = modl[8] * proj[2] + modl[9] * proj[6] + modl[10] * proj[10] + modl[11] * proj[14];
	clip[11] = modl[8] * proj[3] + modl[9] * proj[7] + modl[10] * proj[11] + modl[11] * proj[15];

	clip[12] = modl[12] * proj[0] + modl[13] * proj[4] + modl[14] * proj[8] + modl[15] * proj[12];
	clip[13] = modl[12] * proj[1] + modl[13] * proj[5] + modl[14] * proj[9] + modl[15] * proj[13];
	clip[14] = modl[12] * proj[2] + modl[13] * proj[6] + modl[14] * proj[10] + modl[15] * proj[14];
	clip[15] = modl[12] * proj[3] + modl[13] * proj[7] + modl[14] * proj[11] + modl[15] * proj[15];

	planes.clear();
	Plane newPlane;
	// RIGHT
	newPlane = Plane(clip[3] - clip[0], clip[7] - clip[4], clip[11] - clip[8], clip[15] - clip[12]);
	//newPlane.Normalize();
	planes.push_back(newPlane);
	// LEFT
	newPlane = Plane(clip[3] + clip[0], clip[7] + clip[4], clip[11] + clip[8], clip[15] + clip[12]);
	//newPlane.Normalize();
	planes.push_back(newPlane);
	// BOTTOM
	newPlane = Plane(clip[3] + clip[1], clip[7] + clip[5], clip[11] + clip[9], clip[15] + clip[13]);
	//newPlane.Normalize();
	planes.push_back(newPlane);
	// TOP
	newPlane = Plane(clip[3] - clip[1], clip[7] - clip[5], clip[11] - clip[9], clip[15] - clip[13]);
	//newPlane.Normalize();
	planes.push_back(newPlane);
	// FAR
	newPlane = Plane(clip[3] - clip[2], clip[7] - clip[6], clip[11] - clip[10], clip[15] - clip[14]);
	//newPlane.Normalize();
	planes.push_back(newPlane);
	// NEAR
	newPlane = Plane(clip[3] + clip[2], clip[7] + clip[6], clip[11] + clip[10], clip[15] + clip[14]);
	//newPlane.Normalize();
	planes.push_back(newPlane);
}

vector<Plane> CameraFrustum::GetPlanes() {
	return planes;
}

bool CameraFrustum::IsBBoxInside(const Transform& transform, const BoundingBox& bbox) {
	BoundingBox transformedBbox = transform * bbox;
	return IsBBoxInside(transformedBbox);
}

bool CameraFrustum::IsBBoxInside(const BoundingBox& bbox) {
	int totalIn = 0;
	vector<Vector3> corners = bbox.corners;
	for (int p = 0; p < 6; ++p) {
		int countIn = 8;
		int partialIn = 1;
		for (int i = 0; i < 8; ++i) {
			if (planes[p].DistanceToPoint(corners[i]) < 0) {
				partialIn = 0;
				--countIn;
			}
		}
		if (countIn == 0)
			return false;
		countIn += partialIn;
	}
	if (totalIn == 6)
		return true;
	return true;
}

bool CameraFrustum::IsPointInside(const Vector3& point) {
	for (int i = 0; i < 6; i++) {
		if (planes[i].DistanceToPoint(point) < 0)
			return false;
	}
	return true;
}
