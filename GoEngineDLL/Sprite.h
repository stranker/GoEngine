#pragma once
#include "Entity2D.h"
#include "Texture.h"

class ENGINEDLL_API Sprite :
	public Entity2D {
private:
	Texture *texture;
	GLuint uvBuffer;
	unsigned int textureBuffer;
	bool flipVertical = false;
	bool flipHorizontal = false;
public:
	glm::vec2 GetSize();
	void SetTexture(Texture *_texture);
	void SetTexture(const char* filePath, ImageType imageType);
	Texture *GetTexture();
	void SetUVVertex(float *data, int dataSize);
	void Draw() override;
	void Destroy() override;
	void FlipVertical(bool value);
	void FlipHorizontal(bool value);
	Sprite(Renderer *_renderer);
	virtual ~Sprite();
};

