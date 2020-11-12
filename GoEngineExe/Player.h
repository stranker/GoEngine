#pragma once
#include "BaseGame.h"

class Player{
private:
	AnimatedSprite* animSprite;
	Vector2 velocity;
	float movementSpeed = 300;
public:
	Sprite *GetSprite() const;
	void ManageCollision(CollisionInfo collision);
	void ManageCollision(vector<CollisionInfo> collisions);
	void Update(float deltaTime);
	Player();
	~Player();
};
