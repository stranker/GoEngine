#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include "Exports.h"
#include "Window.h"

class ENGINEDLL_API BaseGame
{
private:
	Window *window;
public:
	bool free();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();
};

