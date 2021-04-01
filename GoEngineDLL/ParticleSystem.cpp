#include "ParticleSystem.h"

ParticleSystem::Particle::Particle() {
	position = Vector2().Zero();
	velocity = Vector2().Zero();
	color = Color();
	lifeTime = 0;
}

void ParticleSystem::SetLifetime(float lifetime) {
	particleLifetime = lifetime;
}

void ParticleSystem::SetParticleCount(uint32_t value) {
	particleCount = value;
	particles.clear();
	for (unsigned int i = 0; i < particleCount; i++) {
		Particle p;
		RandomizeParticle(p);
		particles.push_back(p);
	}
}

void ParticleSystem::RandomizeParticle(Particle& p) {
	p.position = Vector2().Zero();
	float randNumber = Utils::RandRange(0, 1.0); // entre 0 y 1
	float minAngle = Utils::RadToDeg(direction.Angle()) - spread * 0.5;
	float maxAngle = Utils::RadToDeg(direction.Angle()) + spread * 0.5;
	float newAngle = Utils::RandRange(minAngle, maxAngle);
	float randVelocity = randNumber < velocityRandom ? initialVelocity * (1.0 - randNumber) : initialVelocity;
	p.velocity = Vector2(glm::cos(Utils::DegToRad(newAngle)), glm::sin(Utils::DegToRad(newAngle))).Normalize() * randVelocity;
	p.lifeTime = randNumber < explosiveness ? particleLifetime : Utils::RandRange(0, 1);
	p.color.a = 1.0;
}

void ParticleSystem::SetInitialVelocity(float velocity) {
	initialVelocity = velocity;
}

void ParticleSystem::SetVelocityRandom(float velocity) {
	velocityRandom = velocity;
	velocityRandom = Utils::Clamp(velocityRandom, 0.0, 1.0);
}

void ParticleSystem::SetExplosiveness(float explo) {
	explosiveness = explo;
}

void ParticleSystem::SetDirection(Vector2 dir) {
	direction = dir;
}

void ParticleSystem::SetSpread(float angle) {
	spread = angle;
}

void ParticleSystem::SetEmitting(bool val) {
	isEmitting = val;
	SetParticleCount(particleCount);
}

void ParticleSystem::SetTexture(const char * filePath, ImageType imageType) {
	texture = new TextureMaterial();
	texture->LoadShaders("Shaders/ParticleVertexShader.shader", "Shaders/ParticleFragmentShader.shader");
	texture->LoadTexture(filePath, imageType);
	textureBuffer = renderer->CreateTextureBuffer(texture->GetData(), texture->GetWidth(), texture->GetHeight(), texture->GetNrChannels());
	Scale(texture->GetSize());
}

void ParticleSystem::SetFinalColor(Color col) {
	finalColor = col;
}

void ParticleSystem::Update(float deltaTime) {
	if (!isEmitting) {
		return;
	}
	for (unsigned int i = 0; i < particleCount; ++i) {
		Particle &p = particles[i];
		p.lifeTime -= deltaTime;
		if (p.lifeTime > 0.0f) {
			p.position = p.position + p.velocity * deltaTime;
			p.color = initialColor.Interpolate(finalColor,  1 - (p.lifeTime / particleLifetime));
		}
		if (p.lifeTime <= 0.0f) {
			RandomizeParticle(p);
		}
	}
}

void ParticleSystem::Draw() {
	if (!isEmitting) {
		return;
	}
	if (texture) {
		texture->Use();
		texture->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
		texture->SetTextureProperty("sprite", textureBuffer);
	}
	for (Particle particle : particles) {
		if (particle.lifeTime > 0) {
			if (texture) {
				texture->SetVec2("offset", particle.position);
				texture->SetVec4("color", Rect2(particle.color.r, particle.color.g, particle.color.b, particle.color.a));
			}
			renderer->Draw(GetVertexArrayID(), primitive, 6, true);
		}
	}
}

void ParticleSystem::Destroy() {
	if (texture) {
		texture->Destroy();
		delete texture;
	}
}

ParticleSystem::ParticleSystem(Renderer * rend) : Sprite(rend) {
}

ParticleSystem::~ParticleSystem() {
}
