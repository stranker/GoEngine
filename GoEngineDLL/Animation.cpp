#include "Animation.h"

void Animation::Play() {
	isPlaying = true;
}

void Animation::Update(float deltaTime) {
	if (!isPlaying) {
		return;
	}
	internalTimer += deltaTime;
	if (internalTimer >= animFrameLenght) {
		UpdateAnimation();
		internalTimer -= animFrameLenght;
	}
}

void Animation::UpdateAnimation() {
	if (sprite) {
		currentFrame++;
		if (currentFrame >= totalFrames) {
			if (isLooped) {
				currentFrame = 0;
				sprite->SetCurrentFrame(animationFrames[currentFrame]);
			}
			else {
				isPlaying = false;
			}
		}
		else {
			sprite->SetCurrentFrame(animationFrames[currentFrame]);
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
	animFrameLenght = 1.0 / animSpeed;
	if (sprite) {
		sprite->SetCurrentFrame(animationFrames[currentFrame]);
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
