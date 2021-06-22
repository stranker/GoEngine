#pragma once

#include "BaseGame.h"
#include "GameCamera.h"
#include "Tank.h"
#include "TankBullet.h"
#include "Mine.h"

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
	SpotLight* spotLight;
	DirectionalLight* dirLight;
	SpatialMaterial* cubeMaterial;
	Tank* tank;
	Node3D* minesParent;
	TankBullet* tankBullet;
	vector<TankBullet*> bullets;
	vector<Mine*> mines;
	void CreateBullets(int count);
	void CreateMines(int count);
	void ShowMinesGUI();
public:
	void Update(float delta) override;
	void Start() override;
	void Stop() override;
	Game(int _screenWidth, int _screenHeight, const char* _screenTitle);
};
