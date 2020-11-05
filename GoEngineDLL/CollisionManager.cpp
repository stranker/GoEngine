#include "CollisionManager.h"

CollisionInfo CollisionManager::CheckCollision(const Sprite & s1, const Sprite & s2) {
	CollisionInfo colInfo;
	
	// AABB
	bool collisionX = s1.GetPosition().x + s1.GetSize().x >= s2.GetPosition().x &&
		s2.GetPosition().x + s2.GetSize().x >= s1.GetPosition().x;

	bool collisionY = s1.GetPosition().y + s1.GetSize().y >= s2.GetPosition().y &&
		s2.GetPosition().y + s2.GetSize().y >= s1.GetPosition().y;

	colInfo.isColliding = collisionX && collisionY;

	if (!colInfo.isColliding) {
		return colInfo;
	}

	Vector2 diff = Vector2().Zero();
	Vector2 displacement = Vector2().Zero();

	// Calculo la profundidad
	if (s1.GetPosition().x < s2.GetPosition().x) { // Vengo por izquierda
		diff.x = s2.GetPosition().x - (s1.GetPosition().x + s1.GetSize().x);
	}
	else if (s1.GetPosition().x > s2.GetPosition().x) { // Vengo por derecha
		diff.x = s1.GetPosition().x - (s2.GetPosition().x + s2.GetSize().x);
	}
	if (s1.GetPosition().y < s2.GetPosition().y) { // Vengo por arriba
		diff.y = s2.GetPosition().y - (s1.GetPosition().y + s1.GetSize().y);
	}
	else if (s1.GetPosition().y > s2.GetPosition().y) { // Vengo por abajo
		diff.y = s1.GetPosition().y - (s2.GetPosition().y + s2.GetSize().y);
	}

	// Calculo el displacement
	if (abs(diff.x) < abs(diff.y)) {
		if (s1.GetPosition().x < s2.GetPosition().x) { // vengo por izquierda
			displacement.x = diff.x;
		}
		else if(s1.GetPosition().x > s2.GetPosition().x){ // vengo por derecha
			displacement.x = -diff.x;
		}
	}
	else if (abs(diff.x) > abs(diff.y)) {
		if (s1.GetPosition().y < s2.GetPosition().y) { // vengo por arriba
			displacement.y = diff.y;
		}
		else if (s1.GetPosition().y > s2.GetPosition().y) { // vengo por abajo
			displacement.y = -diff.y;
		}
	}
	colInfo.diff = diff;
	colInfo.displacement = displacement;
	return colInfo;
}
