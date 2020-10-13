#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <iterator>
#include "Exports.h"
#include "Window.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Square.h"
#include "Input.h"

class ENGINEDLL_API BaseGame
{
private:
	Window *window;
	Renderer *renderer;
	Input *input;

	Square *square;
	Material *material;
	std::list<Entity*> *entityList;
	std::list<Entity*>::iterator eLIterator;

public:
	bool Init();
	bool Destroy();
	void Loop();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Stop() = 0;

	//=======================================
	void CreateTriangle(float _x, float _y);
};

