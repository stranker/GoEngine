#include "Sprite.h"

Vector2 Sprite::GetSize() const{
	return spriteSize;
}

void Sprite::AddFramesRect() {
	for (size_t i = 0; i < totalFrames; i++) {
		float frameX = (i % verticalFrames) * spriteSize.x;
		float frameY = floor(i / verticalFrames) * spriteSize.y;

		// Calculan la esquina de la imagen ya invertida. TR <-> BR, TL <-> BL
		UVFrame uvFrame;
		uvFrame.tr.x = (frameX + spriteSize.x) / texture->GetSize().x;
		uvFrame.tr.y = (frameY + spriteSize.y) / texture->GetSize().y;

		uvFrame.br.x = (frameX + spriteSize.x) / texture->GetSize().x;
		uvFrame.br.y = frameY / texture->GetSize().y;

		uvFrame.bl.x = frameX / texture->GetSize().x;
		uvFrame.bl.y = frameY / texture->GetSize().y;

		uvFrame.tl.x = frameX / texture->GetSize().x;
		uvFrame.tl.y = (frameY + spriteSize.y) / texture->GetSize().y;

		framesRect.push_back(uvFrame);
	}
}

void Sprite::SetTexture(const char* filePath, int vFrames, int hFrames) {
	texture = new TextureMaterial();
	texture->LoadShaders("Shaders/TextureVertexShader.shader", "Shaders/TextureFragmentShader.shader");
	texture->LoadTexture(filePath);
	textureBuffer = texture->GetTextureID();
	verticalFrames = vFrames;
	horizontalFrames = hFrames;
	totalFrames = verticalFrames * hFrames;
	spriteSize = Vector2(texture->GetSize().x / verticalFrames, texture->GetSize().y / horizontalFrames);
	Scale(spriteSize);
	AddFramesRect();
}

TextureMaterial *Sprite::GetTexture() {
	return texture;
}

void Sprite::Draw() {
	if (texture) {
		texture->Use();
		texture->SetMat4("mvp", Renderer::GetSingleton()->GetCamera()->GetMVPOf(transform->GetTransform()));
		texture->SetTextureProperty("sprite", textureBuffer);
		texture->SetVec4("selfModulate", glm::vec4(selfModulate.r, selfModulate.g, selfModulate.b, selfModulate.a));
		texture->SetBool("flipVertical", flipVertical);
		texture->SetBool("flipHorizontal", flipHorizontal);
	}
	Renderer::GetSingleton()->Draw(GetVertexArrayID(), primitive, draw_vertices, true); // VAO => VBO VBO VBO
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

void Sprite::SetCurrentFrame(unsigned int value) {
	currentFrame = value;
	UVFrame frame = framesRect[currentFrame];
	float uv_vertex_data[] = {
		frame.tr.x, frame.tr.y,
		frame.br.x, frame.br.y,
		frame.bl.x, frame.bl.y,
		frame.tl.x, frame.tl.y
	};
	UpdateVertexData(uv_vertex_data, sizeof(uv_vertex_data), 2); // 2 es el ID del atributo en el shader
}

void Sprite::SetTotalFrames(int value) {
	totalFrames = value;
}

AABB Sprite::GetAABB() const {
	return AABB(GetPosition(), GetSize());
}

Sprite::Sprite() {
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
		1.0f, 1.0f, // tr
		1.0f, 0.0f, // br
		0.0f, 0.0f, // bl
		0.0f, 1.0f // tl
	};
	CreateVertexArrayID(); //crea el VAO
	CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0); // VBO
	CreateVertexData(index_data, sizeof(index_data), 1, Renderer::ELEMENT_BUFFER, -1); // VBO
	CreateVertexData(color_vertex_data, sizeof(color_vertex_data), 4, Renderer::ARRAY_BUFFER, 1); // VBO
	CreateVertexData(uv_vertex_data, sizeof(uv_vertex_data), 2, Renderer::ARRAY_BUFFER, 2); // VBO
	BindVertexObjects(); // Bindeo VAO
	primitive = Renderer::TRIANGLES;
}

Sprite::~Sprite() {
}
