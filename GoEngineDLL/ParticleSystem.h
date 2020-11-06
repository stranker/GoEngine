#pragma once
#include "Exports.h"
#include "Sprite.h"
#include "Utils.h"
#include <vector>

class ENGINEDLL_API ParticleSystem  : public Sprite {
public:
	struct Particle {
		Vector2 position;
		Vector2 velocity;
		Color color;
		float lifeTime;
		Particle();
	};
private:
	TextureMaterial *material;
	uint32_t particleCount;
	vector<Particle> particles;
	Vector2 direction = Vector2().Up();
	Color initialColor;
	Color finalColor;
	float initialVelocity = 1;
	float velocityRandom = 0;
	float particleLifetime = 1;
	float spread = 5;
	bool isEmitting = true;
public:
	void SetParticleCount(uint32_t value);
	void SetInitialVelocity(float velocity);
	void SetVelocityRandom(float velocity);
	void SetDirection(Vector2 dir);
	void SetSpread(float angle);
	void SetEmitting(bool val);
	void SetTexture(const char* filePath, ImageType imageType);
	void SetFinalColor(Color col);
	void Update(float deltaTime);
	void Draw() override;
	void Destroy() override;
	ParticleSystem(Renderer *rend);
	virtual ~ParticleSystem();
};

