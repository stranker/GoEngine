#pragma once
#include "Exports.h"
#include "Sprite.h"

struct CollisionInfo {
	bool isColliding = false;
	Vector2 diff = Vector2().Zero();
	Vector2 displacement = Vector2().Zero();
};

class ENGINEDLL_API CollisionManager {
public:
	static CollisionInfo CheckCollision(const Sprite &s1, const Sprite &s2);
};
