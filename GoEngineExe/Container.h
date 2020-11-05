#pragma once
#include "BaseGame.h"

class Container{
private:
	Sprite *sprite;
	Vector2 velocity;
	float movementSpeed = 200;
	int direction = 1;
public:
	Sprite *GetSprite() const;
	void Update(float deltaTime);
	Container();
	~Container();
};

