#pragma once
#include "BaseGame.h"

class Player{
private:
	Sprite* animSprite;
	Vector2 velocity;
	float movementSpeed = 300;
	Vector2 initialPos;
public:
	Sprite *GetSprite() const;
	void ManageCollision(CollisionInfo collision);
	void ManageCollision(vector<CollisionInfo> collisions);
	void Update(float deltaTime);
	Player();
	~Player();
};
