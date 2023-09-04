#pragma once
#include "Resource.h"

class ENGINEDLL_API Texture : public Resource {
private:
	unsigned int textureId = 0;
	int width = 0;
	int height = 0;
	int nrChannels = 0;
	string path;
	bool isValid = false;
public:
	void CreateTexture(unsigned char* data, int _width, int _height, int _nrChannels, string const& path);
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetNrChannels() const {	return nrChannels; }
	Vector2 GetSize() const { return Vector2(width, height); };
	unsigned int GetTextureID() const { return textureId; };
	bool IsValid() { return isValid; };
	string GetPath() const { return path; };
	Texture() {};
};

class ENGINEDLL_API TextureImporter {
public:
	static Texture LoadTexture(string const& filePath);
	TextureImporter() { };
	~TextureImporter() {};
};

