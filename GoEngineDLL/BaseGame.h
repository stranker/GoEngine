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
#include "AnimatedSprite.h"

class ENGINEDLL_API BaseGame
{
protected:
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Stop() = 0;
	bool InitEngine();
	bool DestroyEngine();
	void LoopEngine();
	static BaseGame *singleton;
private:
	Window *window;
	Renderer *renderer;
	Input *input;
	list<Entity*> *entityList;
	list<Entity*>::iterator entityIterator;
	double currentFrame = glfwGetTime();
	double lastFrame = currentFrame;
	double deltaTime;
public:
	static BaseGame * GetSingleton();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

#pragma region UserMethods

	//ENTITIES
	Sprite* CreateSprite(const char* filePath, ImageType imageType);
	AnimatedSprite* CreateAnimSprite(const char* filePath, ImageType imageType);
	void DrawEntities();

#pragma endregion
};

