#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Exports.h"
#include "Window.h"
#include "Renderer.h"

class ENGINEDLL_API BaseGame
{
private:
	Window *window;
	Renderer *renderer;
public:
	bool Init();
	bool Destroy();
	void Loop();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();
};

