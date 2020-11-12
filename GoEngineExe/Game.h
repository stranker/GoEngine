#pragma once

#include "BaseGame.h"
#include "Player.h"
#include "Container.h"
#include "Dragon.h"

class Game :
	public BaseGame
{
private:
	Player* player;
	Container* container;
	Dragon* dragon;
	Tilemap* tilemap;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	void LoopGame();
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();
};

