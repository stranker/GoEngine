#pragma once
#include "BaseGame.h"

class Dragon{
private:
	AnimatedSprite* sprite;
public:
	Sprite *GetSprite() const;
	void Update(float deltaTime);
	Dragon();
	~Dragon();
};

