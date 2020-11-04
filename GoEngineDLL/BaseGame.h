#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <iterator>
#include "Exports.h"

class Window;
class Renderer;
class Input;
class Sprite;
class AnimatedSprite;
class Entity;

#include "TextureImporter.h"
#include "Vector2.h"
#include "KeyCode.h"

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
	double currentFrame;
	double lastFrame;
	double deltaTime;
public:
	static BaseGame * GetSingleton();
	BaseGame(int _screen_width, int _screen_height, const char* _screen_title);
	virtual ~BaseGame();

#pragma region UserMethods

	//ENTITIES
	Sprite* CreateSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames);
	AnimatedSprite* CreateAnimSprite(const char* filePath, ImageType imageType, int vFrames, int hFrames);
	void UpdateAnimSprite(AnimatedSprite* _as, float _deltaTime);
	void AddAnimation(AnimatedSprite* _as, const char* animName, unsigned int *frames,
						int framesSize, bool looped, float speed);
	void PlayAnimation(AnimatedSprite* _as, const char * animName);
	//=====================================//
	void FlipSpriteH(Sprite* _entity, bool _flip);
	void FlipSpriteH(AnimatedSprite* _entity, bool _flip);
	void FlipSpriteV(Sprite* _entity, bool _flip);
	void FlipSpriteV(AnimatedSprite* _entity, bool _flip);
	//=====================================//
	Vector2 GetSpriteSize(Sprite* _entity);
	Vector2 GetSpriteSize(AnimatedSprite* _entity);
	//=====================================//
	void DrawEntities();

	//TRANSFORMATIONS
	void SetPosition(Sprite* _entity, float _x, float _y);
	void SetPosition(AnimatedSprite* _entity, float _x, float _y);
	//=====================================//
	void Translate(Sprite* _entity, float _x, float _y);
	void Translate(AnimatedSprite* _entity, float _x, float _y);
	//=====================================//
	void Rotate(Sprite* _entity, float angle);
	void Rotate(AnimatedSprite* _entity, float angle);
	//=====================================//
	void Scale(Sprite* _entity, float _x, float _y);
	void Scale(AnimatedSprite* _entity, float _x, float _y);
	//=====================================//
	Vector2 GetPosition(Sprite* _entity);
	Vector2 GetPosition(AnimatedSprite* _entity);
	//=====================================//
	float GetRotation(Sprite* _entity);
	float GetRotation(AnimatedSprite* _entity);
	//=====================================//
	Vector2 GetScale(Sprite* _entity);
	Vector2 GetScale(AnimatedSprite* _entity);

	//INPUT
	bool KeyPressed(KeyCode _key);

	//WINDOW
	Vector2 GetWindowSize();

#pragma endregion
};

