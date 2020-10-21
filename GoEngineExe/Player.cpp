#include "Player.h"

void Player::Update(float deltaTime) {
	velocity = Vector2().Zero();
	if (Input::IsKeyPressed(Input::KEY_W)) {
		velocity.y -= movementSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_S)) {
		velocity.y += movementSpeed;
	}
	if (Input::IsKeyPressed(Input::KEY_A)) {
		velocity.x -= movementSpeed;
		FlipV(true);
	}
	if (Input::IsKeyPressed(Input::KEY_D)) {
		velocity.x += movementSpeed;
		FlipV(false);
	}
	sprite->Translate(velocity * deltaTime);
}

Player::Player() {

}

Player::~Player() {
}
