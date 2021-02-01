#pragma once
#include "Exports.h"
#include <iostream>

using namespace std;
enum ImageType { IMAGETYPE_PNG, IMAGETYPE_JPG, IMAGETYPE_BMP };

struct ENGINEDLL_API TextureData {
	ImageType imageType;
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
};

class ENGINEDLL_API TextureImporter {
public:
	static TextureData LoadTexture(const char * filePath, ImageType imageType);
	static void FreeTexture(TextureData textureData);
	TextureImporter();
	~TextureImporter();
};

