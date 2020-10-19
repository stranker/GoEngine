#include "Sprite.h"


glm::vec2 Sprite::GetSize() {
	return glm::vec2(texture->GetWidth(), texture->GetHeight());
}

void Sprite::SetTexture(Texture * _texture) {
	texture = _texture;
}

void Sprite::SetTexture(const char* filePath, TextureData::ImageType imageType) {
	texture = new Texture();
	texture->LoadShaders("TextureVertexShader.shader", "TextureFragmentShader.shader");
	texture->LoadTexture(filePath, imageType);
	textureBuffer = renderer->CreateTextureBuffer(texture->GetData(), texture->GetWidth(), texture->GetHeight(), texture->GetNrChannels());
	SetScale(GetSize().x, GetSize().y, 0);
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
	SetScale(1, 1, 1);
}

Sprite::~Sprite() {
}
