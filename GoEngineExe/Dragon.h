#pragma once
#include "BaseGame.h"
#include "Player.h"

class Dragon{
private:
	AnimatedSprite* sprite;
	ParticleSystem* fire;
	Player *player;
public:
	Sprite *GetSprite() const;
	void Update(float deltaTime);
	void SetPlayer(Player *p);
	Dragon();
	~Dragon();
};

