#include "TextureMaterial.h"
#include "GlInclude.h"
#include "Sprite.h"

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

void TextureMaterial::SetTextureProperty(string const& propertyName, unsigned int textureId) {
	glActiveTexture(GL_TEXTURE0);
	unsigned int location = glGetUniformLocation(ID, propertyName.c_str());
	glUniform1i(location, textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void TextureMaterial::LoadTexture(const char* filePath) {
	textureData = TextureImporter::LoadTexture(filePath);
}

TextureMaterial::TextureMaterial(){
}

TextureMaterial::~TextureMaterial() {
}
