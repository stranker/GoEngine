#pragma once
#include "Exports.h"
#include <iostream>

using namespace std;

struct ENGINEDLL_API TextureData {
	unsigned int textureId;
	int width;
	int height;
	int nrChannels;
	unsigned char* data;
	string path;
	string name;
	bool isValid = false;

	int GetWidth() const { return width; }
	int Getheight() const { return height; }
	int GetNrChannels() const {	return nrChannels; }
	unsigned int GetID() const { return textureId; };
	unsigned char* GetData() { return data;	}
	bool IsValid() { return isValid; };
};

class ENGINEDLL_API TextureImporter {
public:
	static TextureData LoadTexture(const char* filePath);
	static void FreeTexture(unsigned char* textureData);
	TextureImporter();
	~TextureImporter();
};

