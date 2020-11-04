#include "Dragon.h"

void Dragon::Update(float deltaTime) {
	BaseGame::GetSingleton()->UpdateAnimSprite(sprite,deltaTime);
}

Dragon::Dragon() {
	sprite = BaseGame::GetSingleton()->CreateAnimSprite("dragon.png", IMAGETYPE_PNG, 3, 4);
	unsigned int idle[] = { 3, 4, 5, 4};
	BaseGame::GetSingleton()->AddAnimation(sprite, "idle", idle, 4, true, 8);
	BaseGame::GetSingleton()->PlayAnimation(sprite, "idle");
	BaseGame::GetSingleton()->SetPosition(sprite, 500, 200);
}

Dragon::~Dragon() {
}
