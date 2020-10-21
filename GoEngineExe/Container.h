#pragma once
#include <Object.h>

class Container : 
	public Object {
private:
	Vector2 velocity;
	float movementSpeed = 200;
	int direction = 1;
public:
	void Update(float deltaTime) override;
};

