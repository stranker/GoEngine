#pragma once

#include "BaseGame.h"
#include "Player.h"
#include "Dragon.h"

class Game :
	public BaseGame
{
private:
	Player* player;
	Dragon* dragon;
	Tilemap* tilemap;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void UpdateCollisions();
	void Stop() override;
	void LoopGame();
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();
};

