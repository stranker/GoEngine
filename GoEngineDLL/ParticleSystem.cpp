#include "ParticleSystem.h"

ParticleSystem::Particle::Particle() {
	position = Vector2().Zero();
	velocity = Vector2().Zero();
	color = Color();
	lifeTime = 1.0f;
}

void ParticleSystem::SetParticleCount(uint32_t value) {
	particleCount = value;
	particles.clear();
	for (unsigned int i = 0; i < particleCount; i++) {
		Particle p;
		p.position = Vector2().Zero();
		float randNumber = (rand() % 100) / 100.0; // entre 0 y 1
		float minAngle = Utils::RadToDeg(direction.Angle()) - spread * 0.5;
		float maxAngle = Utils::RadToDeg(direction.Angle()) + spread * 0.5;
		float newAngle = minAngle + rand() % (int(maxAngle - minAngle));
		float randVelocity = randNumber < velocityRandom ? initialVelocity * (1.0 - randNumber) : initialVelocity;
		p.velocity = Vector2(glm::cos(Utils::DegToRad(newAngle)), glm::sin(Utils::DegToRad(newAngle))).Normalize() * randVelocity;
		p.lifeTime = 1.0;
		p.color.a = 1.0f;
		particles.push_back(p);
	}
}

void ParticleSystem::SetInitialVelocity(float velocity) {
	initialVelocity = velocity;
}

void ParticleSystem::SetVelocityRandom(float velocity) {
	velocityRandom = velocity;
	velocityRandom = Utils::Clamp(velocityRandom, 0.0, 1.0);
}

void ParticleSystem::SetDirection(Vector2 dir) {
	direction = dir;
}

void ParticleSystem::SetSpread(float angle) {
	spread = angle;
}

void ParticleSystem::SetEmitting(bool val) {
	isEmitting = val;
}

void ParticleSystem::SetTexture(const char * filePath, ImageType imageType) {
	material = new ParticleMaterial();
	material->LoadShaders("ParticleVertexShader.shader", "ParticleFragmentShader.shader");
	material->LoadTexture(filePath, imageType);
	textureBuffer = renderer->CreateTextureBuffer(material->GetData(), material->GetWidth(), material->GetHeight(), material->GetNrChannels());
	Scale(material->GetSize().x, material->GetSize().y);
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
		if (p.lifeTime > 0.0f) {	// particle is alive, thus update
			p.position = p.position + p.velocity * deltaTime;
			p.color = initialColor.Interpolate(finalColor,  1 - (p.lifeTime / particleLifetime));
		}
		if (p.lifeTime <= 0.0f) {
			p.position = Vector2().Zero();
			float randNumber = (rand() % 100) / 100.0; // entre 0 y 1
			float minAngle = Utils::RadToDeg(direction.Angle()) - spread * 0.5;
			float maxAngle = Utils::RadToDeg(direction.Angle()) + spread * 0.5;
			float newAngle = minAngle + rand() % (int(maxAngle - minAngle));
			float randVelocity = randNumber < velocityRandom ? initialVelocity * (1.0 - randNumber) : initialVelocity;
			p.velocity = Vector2(glm::cos(Utils::DegToRad(newAngle)), glm::sin(Utils::DegToRad(newAngle))).Normalize() * randVelocity;
			p.lifeTime = particleLifetime;
			p.color = Color().White();
		}
	}
}

void ParticleSystem::Draw() {
	if (!isEmitting) {
		return;
	}
	for (Particle particle : particles) {
		if (particle.lifeTime > 0) {
			if (material) {
				material->Use();
				material->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
				material->SetTextureProperty("sprite", textureBuffer);
				material->SetVec2("offset", particle.position);
				material->SetVec4("color", Rect2(particle.color.r, particle.color.g, particle.color.b, particle.color.a));
			}
			renderer->BindVertexArray(vertexArrayID);

			renderer->BindBuffer(positionBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer posicion del tipo GL_ARRAY_BUFFER
			renderer->SetAttributePointer(0, 3); // Seteo los atributos del vertice de posicion

			renderer->BindBuffer(colorBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer Color del tipo GL_ARRAY_BUFFER
			renderer->SetAttributePointer(1, 4); // Seteo los atributos del color

			renderer->BindBuffer(uvBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer UV del tipo GL_ARRAY_BUFFER
			renderer->SetAttributePointer(2, 2); // Seteo los atributos del vertice de UV

			renderer->BindBuffer(indexBuffer, Renderer::ELEMENT_BUFFER);
			renderer->DrawElements(primitive, 6);

			renderer->DisableBuffer(0); // Deshabilito el atributo (pos)
			renderer->DisableBuffer(1); // Deshabilito el atributo (color)
			renderer->DisableBuffer(2); // Deshabilito el atributo (uv)
		}
	}
}

void ParticleSystem::Destroy() {
	if (material) {
		material->Destroy();
		delete material;
	}
}

ParticleSystem::ParticleSystem(Renderer * rend) : Sprite(rend) {
	float position_vertex_data[] = {
		 1.0f,  1.0f, 0.0f,  // top right
		 1.0f,  0.0f, 0.0f,  // bottom right
		 0.0f,  0.0f, 0.0f,  // bottom left
		 0.0f,  1.0f, 0.0f   // top left 
	};
	unsigned int index_data[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float color_vertex_data[] = { selfModulate.r, selfModulate.g, selfModulate.b, selfModulate.a };
	float uv_vertex_data[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
	CreateVertexArrayID();
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 4);
	SetColorVertex(color_vertex_data, sizeof(color_vertex_data));
	SetIndex(index_data, sizeof(index_data));
	SetUVVertex(uv_vertex_data, sizeof(uv_vertex_data));
	primitive = Renderer::TRIANGLES;
}

ParticleSystem::~ParticleSystem() {
}
