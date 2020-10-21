#include "TextureImporter.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

TextureData TextureImporter::LoadTexture(const char * filePath, ImageType imageType) {
	TextureData textureData;
	textureData.imageType = imageType;
	textureData.data = stbi_load(filePath, &textureData.width, &textureData.height, &textureData.nrChannels, imageType == IMAGETYPE_PNG ? STBI_rgb_alpha : STBI_rgb);
	return textureData;
}

void TextureImporter::FreeTexture(TextureData textureData) {
	stbi_image_free(textureData.data);
}

TextureImporter::TextureImporter() {
}

TextureImporter::~TextureImporter() {
}
