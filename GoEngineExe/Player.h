#pragma once
#include <Sprite.h>

class Player {
private:
	Sprite *sprite;
	Vector2 velocity;
	float movementSpeed = 100;
	float testAlpha = 0;
public:
	void AddSprite(Sprite *sprite);
	void SetModulate(Color modulate);
	void SetModulate(float r, float g, float b, float a);
	void FlipH(bool value);
	void FlipV(bool value);
	void Update(float deltaTime);
	void Destroy();
	Player();
	~Player();
};
