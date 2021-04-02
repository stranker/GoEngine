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
	Camera3D* camera;
	Cube* cube;
	Line3D* redLine;
	Line3D* blueLine;
	Line3D* greenLine;
	Gizmo* gizmo;
	vector<Enemy*> enemies;
	CollisionInfo collision;
	vector<CollisionInfo> tilemapCollisions;
	float cameraVelocity = 1;
	float cameraFovIncrement = 1;
	int dir = 1;
	float timer = 0.0f;
	int screenWidth;
	int screenHeight;
	const char* screenTitle;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	void CreateEnemies();
	void CreateEnemy(int attribute, Vector2 position);
	void UpdateCollisions();
	void LoopGame();
	Game(int _screenWidth, int _screenHeight, const char* _screenTitle);
	~Game();
};

