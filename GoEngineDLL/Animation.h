#pragma once
#include "Exports.h"
#include "Sprite.h"
#include <vector>

using namespace std;

class ENGINEDLL_API Animation {
protected:
	Sprite *sprite;
private:
	const char* name;
	int currentFrame;
	bool isLooped;
	bool isPlaying;
	float internalTimer;
	float animSpeed;
	vector<int> animationFrames;
	int totalFrames;
public:
	void Play();
	void Update(float deltaTime);
	void UpdateAnimation();
	void Stop();
	void SetLooped(bool value);
	bool IsPlaying();
	void CreateAnimation(const char* animName, unsigned int * frames, int _totalFrames, bool looped, float _animSpeed);
	Animation(Sprite *_sprite);
	~Animation();
};
