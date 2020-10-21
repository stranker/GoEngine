#pragma once
#include <Object.h>

class Player : public Object {
private:
	Vector2 velocity;
	float movementSpeed = 300;
public:
	void Update(float deltaTime) override;
	Player();
	~Player();
};
