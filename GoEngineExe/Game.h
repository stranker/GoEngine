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
	CollisionInfo collision;
	vector<CollisionInfo> tilemapCollisions;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	void CreateEnemies();
	void CreateEnemy(int attribute, Vector2 position);
	void UpdateCollisions();
	void LoopGame();
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();
};

