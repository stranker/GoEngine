#include "CollisionManager.h"

CollisionInfo CollisionManager::CheckCollision(const AABB & a, const AABB & b) {
	CollisionInfo colInfo;
	bool collisionX = (a.min.x < b.max.x) && (a.max.x > b.min.x);
	bool collisionY = (a.min.y < b.max.y) && (a.max.y > b.min.y);
	colInfo.isColliding = collisionX && collisionY;
	if (!colInfo.isColliding) {
		return colInfo;
	}

	Vector2 diff = Vector2().Zero();
	Vector2 displacement = Vector2().Zero();

	// Calculo la profundidad
	if (a.min.x < b.min.x) { // Vengo por izquierda
		diff.x = b.min.x - a.max.x;
	}
	else if (a.min.x > b.min.x) { // Vengo por derecha
		diff.x = a.min.x - b.max.x;
	}
	if (a.min.y < b.min.y) { // Vengo por arriba
		diff.y = b.min.y - a.max.y;
	}
	else if (a.min.y > b.min.y) { // Vengo por abajo
		diff.y = a.min.y - b.max.y;
	}

	// Calculo el displacement
	if (abs(diff.x) < abs(diff.y)) {
		if (a.min.x < b.min.x) { // vengo por izquierda
			displacement.x = diff.x;
		}
		else if (a.min.x > b.min.x) { // vengo por derecha
			displacement.x = -diff.x;
		}
	}
	else if (abs(diff.x) > abs(diff.y)) {
		if (a.min.y < b.min.y) { // vengo por arriba
			displacement.y = diff.y;
		}
		else if (a.min.y > b.min.y) { // vengo por abajo
			displacement.y = -diff.y;
		}
	}
	colInfo.diff = diff;
	colInfo.displacement = displacement;
	return colInfo;
}

bool SortCollisionsByDiff(CollisionInfo c1, CollisionInfo c2) {
	return c1.displacement.Lenght() > c2.displacement.Lenght();
}

vector<CollisionInfo> CollisionManager::CheckCollision(const AABB &a, const Tilemap& tilemap) {
	vector<CollisionInfo> collisions;
	int maxCollisions = MAX_COLLISIONS;
	for (size_t i = 0; i < tilemap.GetColliderTiles().size(); i++) {
		CollisionInfo colInfo;
		AABB aabbTile = tilemap.GetColliderTiles()[i].GetAABB();
		colInfo = CheckCollision(a, aabbTile);
		if (colInfo.isColliding) {
			collisions.push_back(colInfo);
			maxCollisions--;
		}
		if (maxCollisions <= 0) {
			break;
		}
	}
	if (!collisions.empty()) {
		sort(collisions.begin(), collisions.end(), SortCollisionsByDiff);
	}
	return collisions;
}


