#pragma once

#include "BaseGame.h"

class Game :
	public BaseGame
{
public:
	void Start() override;
	void Update(float deltaTime) override;
	void Stop() override;
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();

	Sprite* nAKELS;
	Triangle* tri;
};

