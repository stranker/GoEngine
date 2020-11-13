#pragma once
#include "Exports.h"
#include "Utils.h"
#include "Tilemap.h"

#define MAX_COLLISIONS 4

struct CollisionInfo {
	bool isColliding = false;
	Vector2 diff = Vector2().Zero();
	Vector2 displacement = Vector2().Zero();
};

class ENGINEDLL_API CollisionManager {
public:
	static CollisionInfo CheckCollision(const AABB &a, const AABB &ab);
	static vector<CollisionInfo> CheckCollision(const AABB &a, const Tilemap& tilemap);
};
