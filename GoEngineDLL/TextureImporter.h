#pragma once
#include "Exports.h"
#include <iostream>

using namespace std;

class ENGINEDLL_API TextureData {
public:
	enum ImageType { IT_PNG, IT_JPG, IT_BMP };
	ImageType imageType;
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
	TextureData() {};
	~TextureData() {};
};

class ENGINEDLL_API TextureImporter {
public:
	static TextureData LoadTexture(const char * filePath, TextureData::ImageType imageType);
	static void FreeTexture(TextureData textureData);
	TextureImporter();
	~TextureImporter();
};

