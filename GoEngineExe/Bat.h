#pragma once
#include "Enemy.h"

class Bat : public Enemy {
private:
	enum States{ IDLE, FLY, LAST};
	vector<Vector2> directions { Vector2().Up(), Vector2().Down(), Vector2().Left(), Vector2().Right()};
	Vector2 currentDirection;
	Vector2 velocity;
	States currentState = IDLE;
	float timer;
	float minTravelTime;
	float maxTravelTime;
	float travelTime;
	float idleTime;
	float movementSpeed = 100;
public:
	void Update(float deltaTime) override;
	void ProcessState(States state, float deltaTime);
	Bat();
	virtual ~Bat();
};

