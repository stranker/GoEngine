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
#include "Sprite.h"

class ENGINEDLL_API BaseGame
{
protected:
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Stop() = 0;
private:
	Window *window;
	Renderer *renderer;
	Input *input;
	Material *material;
	list<Entity*> *entityList;
	list<Entity*>::iterator entityIterator;
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
public:
	bool InitEngine();
	bool DestroyEngine();
	void LoopEngine();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();
	void CreateSprite(float x, float y);
	void CreateTriangle(float _x, float _y);
	void UpdateEntities(float deltaTime);
	void DrawEntities();
};

