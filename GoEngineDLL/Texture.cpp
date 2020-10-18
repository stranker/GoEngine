#include "Texture.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION


void Texture::Destroy() {
	stbi_image_free(textureData);
	glDeleteProgram(ID);
}

int Texture::GetWidth() const {
	return width;
}

int Texture::GetHeight() const {
	return height;
}

unsigned char * Texture::GetData() const {
	return textureData;
}

void Texture::SetTextureProperty(const char * property, unsigned int value) {
	unsigned int location = glGetUniformLocation(ID, property);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, value);
	glUniform1i(location, 0);
}

void Texture::LoadTexture(const char * filePath) {
	int nrChannels;
	textureData = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (textureData) {
		cout << "hay data" << endl;
	}
	else {
		cout << "No se cargo" << endl;
	}
}

Texture::Texture(){
}

Texture::~Texture() {
}
