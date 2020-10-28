#include "Animation.h"

void Animation::Play() {
	isPlaying = true;
}

void Animation::Update(float deltaTime) {
	if (!isPlaying) {
		return;
	}
	if (internalTimer >= 1.0 / animSpeed) {
		UpdateAnimation();
		internalTimer = 0;
	}
	else {
		internalTimer += deltaTime;
	}
}

void Animation::UpdateAnimation() {
	if (sprite) {
		if (currentFrame == totalFrames) {
			if (isLooped) {
				currentFrame = 0;
			}
		}
		else {
			sprite->SetCurrentFrame(animationFrames[currentFrame]);
			currentFrame++;
		}
	}
}

void Animation::Stop() {
	isPlaying = false;
}

void Animation::SetLooped(bool value) {
	isLooped = value;
}

bool Animation::IsPlaying() {
	return isPlaying;
}

void Animation::CreateAnimation(const char * animName, unsigned int * frames, int _totalFrames, bool looped, float _animSpeed) {
	totalFrames = _totalFrames;
	for (size_t i = 0; i < totalFrames; i++) {
		animationFrames.push_back(frames[i]);
	}
	isLooped = looped;
	animSpeed = _animSpeed;
	if (sprite) {
		sprite->SetCurrentFrame(animationFrames[0]);
	}
}

Animation::Animation(Sprite * _sprite) {
	sprite = _sprite;
	isLooped = false;
	isPlaying = false;
	internalTimer = 0;
	currentFrame = 0;
	totalFrames = 0;
	animationFrames.clear();
}

Animation::~Animation() {
}
