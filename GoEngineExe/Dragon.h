#pragma once
#include "Enemy.h"
#include "Player.h"

class Dragon : public Enemy{
private:
	ParticleSystem* fire;
	Player *player;
public:
	void Update(float deltaTime) override;
	void SetPlayer(Player *p);
	Dragon();
	~Dragon();
};

