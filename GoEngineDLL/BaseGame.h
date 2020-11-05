#pragma once

#include "Exports.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <iterator>

class Window;
class Renderer;

#include "Utils.h"
#include "Input.h"
#include "AnimatedSprite.h"
#include "CollisionManager.h"

class ENGINEDLL_API BaseGame{
protected:
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Stop() = 0;
	bool InitEngine();
	bool DestroyEngine();
	void LoopEngine();
	void DrawEntities();
	static BaseGame *singleton;
private:
	Window *window;
	Renderer *renderer;
	Input *input;
	list<Entity*> *entityList;
	list<Entity*>::iterator entityIterator;
	double currentFrame;
	double lastFrame;
	double deltaTime;
public:
	static BaseGame *GetSingleton();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

#pragma region UserMethods

	//ENTITIES
	Sprite* CreateSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames);
	AnimatedSprite* CreateAnimSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames);

	//WINDOW
	Vector2 GetWindowSize();

#pragma endregion
};
