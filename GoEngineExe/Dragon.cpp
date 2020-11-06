#include "Dragon.h"

Sprite * Dragon::GetSprite() const {
	return sprite;
}

void Dragon::Update(float deltaTime) {
	if (player) {
		Vector2 dirToPlayer = player->GetSprite()->GetPosition() - sprite->GetPosition();
		fire->SetDirection(dirToPlayer.Normalize());
	}
	sprite->Update(deltaTime);
	fire->Update(deltaTime);
}

void Dragon::SetPlayer(Player * p) {
	player = p;
}

Dragon::Dragon() {
	sprite = BaseGame::GetSingleton()->CreateAnimSprite("dragon.png", IMAGETYPE_PNG, 3, 4);
	unsigned int idle[] = { 3, 4, 5, 4};
	sprite->AddAnimation("idle", idle, 4, true, 8);
	sprite->Play("idle");
	sprite->SetPosition(Vector2(500, 200));

	fire = BaseGame::GetSingleton()->CreateParticleSystem("fire.png", IMAGETYPE_PNG, 15);
	fire->SetPosition(Vector2(480, 220));
	fire->SetSpread(90);
	fire->SetInitialVelocity(10);
	fire->SetVelocityRandom(0.8);
	fire->SetFinalColor(Color(1, 1, 1, 0));
}

Dragon::~Dragon() {
}
