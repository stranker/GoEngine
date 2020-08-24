#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Exports.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

class ENGINEDLL_API BaseGame
{
public:
	int create_window();
	BaseGame();
	virtual ~BaseGame();
};

