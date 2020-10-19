#include "Texture.h"


void Texture::Destroy() {
	TextureImporter::FreeTexture(textureData);
	glDeleteProgram(ID);
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

unsigned char * Texture::GetData() const {
	return textureData.data;
}

void Texture::SetTextureProperty(const char * property, unsigned int value) {
	unsigned int location = glGetUniformLocation(ID, property);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, value);
	glUniform1i(location, 0);
}

void Texture::LoadTexture(const char* filePath, TextureData::ImageType imageType) {
	textureData = TextureImporter::LoadTexture(filePath, imageType);
}

Texture::Texture(){
}

Texture::~Texture() {
}
