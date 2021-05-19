#include "TextureImporter.h"
#include "Renderer.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION

Texture TextureImporter::LoadTexture(string const& filePath) {
	Texture texture;
	int width;
	int height;
	int nrChannels;
	unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		texture.CreateTexture(data, width, height, nrChannels, filePath);
	}
	stbi_image_free(data);
	return texture;
}

void Texture::CreateTexture(unsigned char* _data, int _width, int _height, int _nrChannels, string const& _path) {
	width = _width;
	height = _height;
	nrChannels = _nrChannels;
	path = _path;
	textureId = Renderer::GetSingleton()->CreateTextureBuffer(_data, _width, _height, _nrChannels);
	isValid = true;
}