#include "Player.h"

void Player::Update(float deltaTime) {
	velocity = Vector2().Zero();
	if (BaseGame::GetSingleton()->KeyPressed(KEY_W)) {
		velocity.y -= movementSpeed;
	}
	if (BaseGame::GetSingleton()->KeyPressed(KEY_S)) {
		velocity.y += movementSpeed;
	}
	if (BaseGame::GetSingleton()->KeyPressed(KEY_A)) {
		velocity.x -= movementSpeed;
		BaseGame::GetSingleton()->FlipSpriteV(animSprite, true);
	}
	if (BaseGame::GetSingleton()->KeyPressed(KEY_D)) {
		velocity.x += movementSpeed;
		BaseGame::GetSingleton()->FlipSpriteV(animSprite, false);
	}
	BaseGame::GetSingleton()->UpdateAnimSprite(animSprite, deltaTime);
	BaseGame::GetSingleton()->Translate(animSprite, velocity.x * deltaTime, velocity.y * deltaTime);
}

Player::Player() {
	animSprite = BaseGame::GetSingleton()->CreateAnimSprite("player.png", IMAGETYPE_PNG, 1, 1);
	unsigned int idle[] = {0};
	BaseGame::GetSingleton()->AddAnimation(animSprite, "idle", idle, 1, true, 8);
	BaseGame::GetSingleton()->PlayAnimation(animSprite, "idle");

	BaseGame::GetSingleton()->SetPosition(animSprite, 100, 100);
}

Player::~Player() {
}
