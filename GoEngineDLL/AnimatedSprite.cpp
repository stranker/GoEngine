#include "AnimatedSprite.h"

void AnimatedSprite::AddAnimation(const char* animName, unsigned int *frames, int framesSize, bool looped, float speed) {
	Animation* newAnimation = new Animation(this);
	newAnimation->CreateAnimation(animName, frames, framesSize, looped, speed);
	animations[string(animName)] = newAnimation;
}

void AnimatedSprite::Play(const char * animName) {
	string anim = string(animName);
	bool animFound = false;
	for (animIt = animations.begin(); animIt != animations.end(); animIt++) {
		if (animIt->first == anim && !animFound) {
			currentAnimName = animIt->first;
			currentAnimation = animIt->second;
			currentAnimation->Play();
			animFound = true;
			break;
		}
	}
	if (!animFound) {
		cout << "Animation not found!" << endl;
	}
}

void AnimatedSprite::Stop() {
	for (animIt = animations.begin(); animIt != animations.end(); animIt++) {
		if (animIt->first == currentAnimName) {
			animIt->second->Stop();
			break;
		}
	}
}

void AnimatedSprite::Update(float deltaTime) {
	if (!animations.empty()) {
		if (currentAnimation) {
			currentAnimation->Update(deltaTime);
		}
	}
}

AnimatedSprite::AnimatedSprite(Renderer * _renderer) : Sprite(_renderer){
}

AnimatedSprite::~AnimatedSprite() {
	animations.clear();
}
