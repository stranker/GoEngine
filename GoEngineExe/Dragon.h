#pragma once
#include "BaseGame.h"

class Dragon{
private:
	AnimatedSprite* sprite;
public:
	void Update(float deltaTime);
	Dragon();
	~Dragon();
};

