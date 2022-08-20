#include "ParticleSystem3D.h"

void ParticleSystem3D::Draw() {
}

void ParticleSystem3D::Update(float deltaTime) {
}

ParticleSystem3D::ParticleSystem3D() {
	SetDefaultName(name);
	particleCount = initialCount;
	particleLifetime = initialLifeTime;
	for (size_t i = 0; i < particleCount; i++) {
		Particle3D particle;
		particle.lifeTime = particleLifetime;
		particle.position = Vector3().Zero();
		particles.push_back(particle);
	}
}

ParticleSystem3D::~ParticleSystem3D() {
}