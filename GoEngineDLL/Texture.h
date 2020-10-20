#pragma once
#include "Exports.h"
#include "Material.h"
#include "Renderer.h"
#include "TextureImporter.h"

class ENGINEDLL_API Texture : 
	public Material {
private:
	TextureData textureData;
public:
	int GetWidth() const;
	int GetHeight() const;
	int GetNrChannels() const;
	unsigned char * GetData() const;
	void SetTextureProperty(const char* property, unsigned int value);
	void Destroy();
	void LoadTexture(const char* filePath, ImageType imageType);
	Texture();
	virtual ~Texture();
};

