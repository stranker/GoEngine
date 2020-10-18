#pragma once
#include "Exports.h"
#include "Material.h"
#include "Renderer.h"

class ENGINEDLL_API Texture : 
	public Material {
private:
	int width;
	int height;
	unsigned char *textureData;
public:
	int GetWidth() const;
	int GetHeight() const;
	unsigned char * GetData() const;
	void SetTextureProperty(const char* property, unsigned int value);
	void Destroy();
	void LoadTexture(const char* filePath);
	Texture();
	virtual ~Texture();
};

