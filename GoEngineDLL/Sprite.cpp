#include "Sprite.h"

Vector2 Sprite::GetSize() {
	return Vector2(texture->GetWidth(), texture->GetHeight());
}

void Sprite::SetTexture(Texture * _texture) {
	texture = _texture;
}

void Sprite::SetTexture(const char* filePath, ImageType imageType) {
	texture = new Texture();
	texture->LoadShaders("TextureVertexShader.shader", "TextureFragmentShader.shader");
	texture->LoadTexture(filePath, imageType);
	textureBuffer = renderer->CreateTextureBuffer(texture->GetData(), texture->GetWidth(), texture->GetHeight(), texture->GetNrChannels());
	spriteSize = GetSize();
	Scale(spriteSize.x, spriteSize.y);
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
		texture->SetVec4("selfModulate", glm::vec4(selfModulate.r, selfModulate.g, selfModulate.b, selfModulate.a));
		texture->SetBool("flipVertical", flipVertical);
		texture->SetBool("flipHorizontal", flipHorizontal);
		texture->SetInt("horizontalFrames", horizontalFrames);
		texture->SetInt("verticalFrames", verticalFrames);
		texture->SetInt("currentFrame", currentFrame);
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
	renderer->DisableBuffer(1); // Deshabilito el atributo (uv)
}

void Sprite::Destroy() {
	if (texture) {
		texture->Destroy();
		delete texture;
	}
}

void Sprite::FlipVertical(bool value) {
	flipVertical = value;
}

void Sprite::FlipHorizontal(bool value) {
	flipHorizontal = value;
}

void Sprite::SetVerticalFrames(int value) {
	verticalFrames = value;
	spriteSize.y = int(GetSize().y / verticalFrames);
	Scale(spriteSize.x, spriteSize.y);
}

void Sprite::SetHorizontalFrames(int value) {
	horizontalFrames = value;
	spriteSize.x = int(GetSize().x / horizontalFrames);
	Scale(spriteSize.x, spriteSize.y);
}

void Sprite::SetCurrentFrame(int value) {
	currentFrame = value;
}

void Sprite::SetTotalFrames(int value) {
	totalFrames = value;
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

Sprite::~Sprite() {
}
