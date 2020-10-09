#pragma once

#include "BaseGame.h"
#include "Triangle.h"

class Game :
	public BaseGame
{
public:
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();

	void Start();
	void Update();
	void Stop();
};

