#include "TextureMaterial.h"
#include "GlInclude.h"


void TextureMaterial::Destroy() {
	TextureImporter::FreeTexture(textureData);
}

int TextureMaterial::GetWidth() const {
	return textureData.width;
}

int TextureMaterial::GetHeight() const {
	return textureData.height;
}

int TextureMaterial::GetNrChannels() const {
	return textureData.nrChannels;
}

Vector2 TextureMaterial::GetSize() const {
	return Vector2(textureData.width, textureData.height);
}

unsigned char * TextureMaterial::GetData() const {
	return textureData.data;
}

void TextureMaterial::SetTextureProperty(const char * property, unsigned int value) {
	unsigned int location = glGetUniformLocation(ID, property);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, value);
	glUniform1i(location, 0);
}

void TextureMaterial::LoadTexture(const char* filePath, ImageType imageType) {
	textureData = TextureImporter::LoadTexture(filePath, imageType);
}

TextureMaterial::TextureMaterial(){
}

TextureMaterial::~TextureMaterial() {
}
