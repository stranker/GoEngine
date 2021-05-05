#include "TextureImporter.h"
#include "Renderer.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

TextureData TextureImporter::LoadTexture(const char * filePath) {
	TextureData textureData;
	textureData.data = stbi_load(filePath, &textureData.width, &textureData.height, &textureData.nrChannels, 0);
	textureData.path = string(filePath);
	if (textureData.data){
		textureData.textureId = Renderer::GetSingleton()->CreateTextureBuffer(textureData.data, textureData.width, textureData.height, textureData.nrChannels);
		textureData.isValid = true;
	}
	return textureData;
}

void TextureImporter::FreeTexture(unsigned char* textureData) {
	if (textureData){
		stbi_image_free(textureData);
	}
}

TextureImporter::TextureImporter() {
}

TextureImporter::~TextureImporter() {
}