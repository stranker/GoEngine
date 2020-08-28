#pragma once

#include "BaseGame.h"

class Game :
	public BaseGame
{
public:
	Game(int _screen_width, int _screen_height, const char* _screen_title);
	~Game();
};

