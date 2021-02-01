#include "Bat.h"

void Bat::Update(float deltaTime) {
	Enemy::Update(deltaTime);
	ProcessState(currentState, deltaTime);
	float posX = Utils::Clamp(animSprite->GetPosition().x, 0, BaseGame::GetSingleton()->GetWindowSize().x - GetSprite()->GetSize().x);
	float posY = Utils::Clamp(animSprite->GetPosition().y, 0, BaseGame::GetSingleton()->GetWindowSize().y - GetSprite()->GetSize().y);
	animSprite->SetPosition(posX, posY);
}

void Bat::ProcessState(States state, float deltaTime) {
	switch (state) {
	case Bat::IDLE:
		timer += deltaTime;
		if (timer >= idleTime) {
			timer = 0;
			float randNumber = rand() % directions.size();
			currentDirection = directions[randNumber];
			travelTime = Utils::RandRange(minTravelTime, maxTravelTime);
			currentState = FLY;
		}
		break;
	case Bat::FLY:
		animSprite->Translate(currentDirection * movementSpeed * deltaTime);
		timer += deltaTime;
		if (timer >= travelTime) {
			timer = 0;
			currentState = IDLE;
		}
		break;
	case Bat::LAST:
		break;
	default:
		break;
	}
}

Bat::Bat() {
	animSprite = BaseGame::GetSingleton()->CreateAnimSprite("bat.png", IMAGETYPE_PNG, 4, 4);
	unsigned int idle[] = { 1, 2, 3, 2 };
	animSprite->AddAnimation("idle", idle, 4, true, 8);
	animSprite->Play("idle");
	minTravelTime = 1.0;
	maxTravelTime = 3.0;
	travelTime = Utils::RandRange(minTravelTime, maxTravelTime);
	idleTime = 2.0;
}

Bat::~Bat() {
}
