#pragma once

#include "BaseGame.h"
#include "GameCamera.h"
#include "Card3D.h"
#include "Container.h"

class Game :
	public BaseGame
{
private:
	float timer = 0.0f;
	int screenWidth;
	int screenHeight;
	const char* screenTitle;
	GameCamera* camera;
	Container* container;
	SpotLight* spotLight;
	DirectionalLight* dirLight;
	PointLight* plight;
	PointLight* plight2;
	SpatialMaterial* cubeMaterial;
	Node3D* blenderScene;
	Node3D* link;
public:
	void OnUpdate(float delta) override;
	void Start() override;
	void Stop() override;
	Game(int _screenWidth, int _screenHeight, const char* _screenTitle);
};
