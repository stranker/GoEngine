#pragma once

#include "BaseGame.h"
#include "Player.h"

class Game :
	public BaseGame
{
private:
	Player* player;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();
};

