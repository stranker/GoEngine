#pragma once
#include "Primitive.h"

struct Particle3D {
	Vector3 position;
	Vector3 velocity;
	Color color;
	float lifeTime;
	Particle3D() {};
};

class ParticleSystem3D : public Primitive {
private:
	vector<Particle3D> particles;
	const int initialCount = 10;
	const float initialLifeTime = 1.0;
	int particleCount;
	float particleLifetime;
public:
	virtual void Draw() override;
	virtual void Update(float deltaTime) override;
	ParticleSystem3D();
	~ParticleSystem3D();
};

