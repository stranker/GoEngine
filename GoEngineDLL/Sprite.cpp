#include "Sprite.h"


void Sprite::SetTexture(Texture * _texture) {
	texture = _texture;
}

void Sprite::SetTexture(const char* filePath) {
	texture = new Texture();
	texture->LoadShaders("TextureVertexShader.shader", "TextureFragmentShader.shader");
	texture->LoadTexture(filePath);
	textureBuffer = renderer->CreateTextureBuffer(texture->GetData(), texture->GetWidth(), texture->GetHeight());
}

Texture *Sprite::GetTexture() {
	return texture;
}

void Sprite::SetUVVertex(float * data, int dataSize) {
	uvBuffer = renderer->CreateVertexBuffer(data, dataSize, Renderer::ARRAY_BUFFER);
}

void Sprite::Draw() {
	if (texture) {
		texture->Use();
		texture->SetMat4("mvp", renderer->GetCamera()->GetMVPOf(transform->GetTransform()));
		texture->SetTextureProperty("ourTexture", textureBuffer);
	}
	renderer->BindVertexArray(vertexArrayID);

	renderer->BindBuffer(positionBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer posicion del tipo GL_ARRAY_BUFFER
	renderer->SetAttributePointer(0, 3); // Seteo los atributos del vertice de posicion

	renderer->BindBuffer(uvBuffer, Renderer::ARRAY_BUFFER); // Bindeo el buffer UV del tipo GL_ARRAY_BUFFER
	renderer->SetAttributePointer(1, 2); // Seteo los atributos del vertice de UV

	renderer->BindBuffer(indexBuffer, Renderer::ELEMENT_BUFFER);
	renderer->DrawElements(primitive, 6);

	renderer->DisableBuffer(0); // Deshabilito el atributo (pos)
	renderer->DisableBuffer(1); // Deshabilito el atributo (uv)
}

void Sprite::Update(float deltaTime) {
	glm::vec2 velocity = glm::vec2(0.0f);
	if (input->IsKeyPressed(Input::KEY_A)) {
		velocity.x = -100;
	}
	if (input->IsKeyPressed(Input::KEY_D)) {
		velocity.x = 100;
	}
	if (input->IsKeyPressed(Input::KEY_W)) {
		velocity.y = 100;
	}
	if (input->IsKeyPressed(Input::KEY_S)) {
		velocity.y = -100;
	}
	Translate(velocity.x * deltaTime, velocity.y * deltaTime);
}

void Sprite::Destroy() {
	if (texture) {
		texture->Destroy();
		delete texture;
	}
}

Sprite::Sprite(Renderer *_renderer) : Entity2D(_renderer) {
	float position_vertex_data[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int index_data[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	float uv_vertex_data[] = {
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f
	};
	CreateVertexArrayID();
	SetPositionVertex(position_vertex_data, sizeof(position_vertex_data), 4);
	SetIndex(index_data, sizeof(index_data));
	SetUVVertex(uv_vertex_data, sizeof(uv_vertex_data));
	primitive = Renderer::TRIANGLES;
	SetScale(64.0f, 64.0f, 0.0f);
}

Sprite::~Sprite() {
}
