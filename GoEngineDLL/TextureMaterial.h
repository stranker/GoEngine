#pragma once
#include "Exports.h"
#include "Material.h"
#include "TextureImporter.h"

class ENGINEDLL_API TextureMaterial : 
	public Material {
private:
	TextureData textureData;
public:
	int GetWidth() const;
	int GetHeight() const;
	int GetNrChannels() const;
	Vector2 GetSize() const;
	unsigned char * GetData() const;
	void SetTextureProperty(string const& propertyName, unsigned int textureId);
	void LoadTexture(const char* filePath);
	unsigned int GetTextureID() const { return textureData.GetID(); };
	TextureMaterial();
	virtual ~TextureMaterial();
};

