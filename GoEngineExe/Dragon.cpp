#include "Dragon.h"

void Dragon::Update(float deltaTime) {
	Enemy::Update(deltaTime);
	if (player) {
		Vector2 dirToPlayer = player->GetSprite()->GetPosition() - animSprite->GetPosition();
		fire->SetDirection(dirToPlayer.Normalize());
		fire->SetPosition(animSprite ->GetPosition() + Vector2(-5, 20));
	}
	fire->Update(deltaTime);
}

void Dragon::SetPlayer(Player * p) {
	player = p;
}

Dragon::Dragon() {
	animSprite = BaseGame::GetSingleton()->CreateAnimSprite("dragon.png", IMAGETYPE_PNG, 3, 4);
	unsigned int idle[] = { 3, 4, 5, 4};
	animSprite->AddAnimation("idle", idle, 4, true, 8);
	animSprite->Play("idle");

	fire = BaseGame::GetSingleton()->CreateParticleSystem("fire.png", IMAGETYPE_PNG, 15);
	fire->SetSpread(90);
	fire->SetInitialVelocity(10);
	fire->SetVelocityRandom(0.8);
	fire->SetFinalColor(Color(1, 1, 1, 0));
}

Dragon::~Dragon() {
}
