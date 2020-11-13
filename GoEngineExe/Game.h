#pragma once

#include "BaseGame.h"
#include "Player.h"
#include "Dragon.h"
#include "Bat.h"

class Game :
	public BaseGame
{
private:
	Player* player;
	Tilemap* tilemap;
	vector<Enemy*> enemies;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void CreateEnemies();
	void CreateEnemy(int attribute, Vector2 position);
	void UpdateCollisions();
	void Stop() override;
	void LoopGame();
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();
};

