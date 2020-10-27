#pragma once
#include "BaseGame.h"

class Player{
private:
	AnimatedSprite* animSprite;
	Vector2 velocity;
	float movementSpeed = 300;
public:
	void Update(float deltaTime);
	Player();
	~Player();
};
