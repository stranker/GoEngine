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
	if (abs(diff.x) < abs(diff.y)) { // Colision en X
		if (a.min.x < b.min.x) { // vengo por izquierda
			displacement.x = diff.x;
		}
		else if (a.min.x > b.min.x) { // vengo por derecha
			displacement.x = -diff.x;
		}
	}
	else if (abs(diff.x) > abs(diff.y)) { // Colision en Y
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

	// Obtengo los tiles de mi alrededor
	int left_tile = a.min.x / tilemap.GetTileSize().x;
	int right_tile = a.max.x / tilemap.GetTileSize().x;
	int top_tile = a.min.y / tilemap.GetTileSize().y;
	int bottom_tile = a.max.y / tilemap.GetTileSize().y;

	// Clampeo los tiles obtenidos entre 0 y el tamanio del mapa
	if (left_tile < 0) left_tile = 0;
	if (right_tile > tilemap.GetMapSize().x) right_tile = tilemap.GetMapSize().x;
	if (top_tile < 0) top_tile = 0;
	if (bottom_tile > tilemap.GetMapSize().y) bottom_tile = tilemap.GetMapSize().y;

	// Itero sobre los tiles de mi alrededor y checkeo si son colisionables
	for (int i = left_tile; i <= right_tile; i++) {
		for (int j = top_tile; j <= bottom_tile; j++) {
			if (tilemap.IsColliderTile(Vector2(i, j))) {
				CollisionInfo colInfo = CheckCollision(a, tilemap.GetColliderTileAt(Vector2(i, j)).GetAABB());
				if (colInfo.isColliding) {
					collisions.push_back(colInfo);
				}
			}
		}
	}
	return collisions;
}


