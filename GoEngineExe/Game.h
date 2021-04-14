#pragma once

#include "BaseGame.h"
#include "GameCamera.h"

class Game :
	public BaseGame
{
private:
	GameCamera* camera;
	Cube* cube;
	Light* light;
	float cameraVelocity = 1;
	float cameraFovIncrement = 1;
	int dir = 1;
	float timer = 0.0f;
	float xLast;
	float yLast;
	int screenWidth;
	int screenHeight;
	const char* screenTitle;
	SpatialMaterial* cubeMaterial;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	void LoopGame();
	Game(int _screenWidth, int _screenHeight, const char* _screenTitle);
	~Game();
};

