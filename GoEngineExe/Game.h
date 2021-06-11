#pragma once

#include "BaseGame.h"
#include "GameCamera.h"
#include "Tank.h"

class Game :
	public BaseGame
{
private:
	float timer = 0.0f;
	int screenWidth;
	int screenHeight;
	const char* screenTitle;
	GameCamera* camera;
	Cube* cube;
	Cube* cube2;
	Cube* cube3;
	SpotLight* spotLight;
	DirectionalLight* dirLight;
	SpatialMaterial* cubeMaterial;
	Node3D* cat;
	Tank* tank;
	MeshInstance* minecraft;
	MeshInstance* beer;
	MeshInstance* wizard;
	MeshInstance* reptile;
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	void LoopGame();
	Game(int _screenWidth, int _screenHeight, const char* _screenTitle);
};

