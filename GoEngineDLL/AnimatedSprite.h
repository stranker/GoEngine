#ifndef ENGINE_3D
#pragma once
#include "Sprite.h"
#include "Animation.h"
#include <map>

class ENGINEDLL_API AnimatedSprite :
	public Sprite {
private:
	map<string, Animation*> animations;
	map<string, Animation*>::iterator animIt;
	string currentAnimName;
	Animation* currentAnimation;
public:
	void AddAnimation(const char* animName, unsigned int* frames, int framesSize, bool looped, float speed);
	void Play(const char* animName);
	void Stop();
	void Resume();
	void Update(float deltaTime) override;
	AnimatedSprite();
	~AnimatedSprite();
};
#endif // !ENGINE_3D


