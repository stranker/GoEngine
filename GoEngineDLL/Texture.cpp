#include "Texture.h"


void Texture::Destroy() {
	TextureImporter::FreeTexture(textureData);
}

int Texture::GetWidth() const {
	return textureData.width;
}

int Texture::GetHeight() const {
	return textureData.height;
}

int Texture::GetNrChannels() const {
	return textureData.nrChannels;
}

Vector2 Texture::GetSize() const {
	return Vector2(textureData.width, textureData.height);
}

unsigned char * Texture::GetData() const {
	return textureData.data;
}

void Texture::SetTextureProperty(const char * property, unsigned int value) {
	unsigned int location = glGetUniformLocation(ID, property);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, value);
	glUniform1i(location, 0);
}

void Texture::LoadTexture(const char* filePath, ImageType imageType) {
	textureData = TextureImporter::LoadTexture(filePath, imageType);
}

Texture::Texture(){
}

Texture::~Texture() {
}
