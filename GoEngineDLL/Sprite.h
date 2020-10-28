#pragma once
#include "Entity2D.h"
#include "TextureMaterial.h"

class ENGINEDLL_API Sprite :
	public Entity2D {
private:
	TextureMaterial *texture;
	GLuint uvBuffer;
	unsigned int textureBuffer;
	bool flipVertical = false;
	bool flipHorizontal = false;
	int verticalFrames = 1;
	int horizontalFrames = 1;
	int currentFrame = 0;
	int totalFrames = 1;
	Vector2 spriteSize;
public:
	Vector2 GetSize();
	void SetTexture(TextureMaterial *_texture);
	void SetTexture(const char* filePath, ImageType imageType);
	TextureMaterial *GetTexture();
	void SetUVVertex(float *data, int dataSize);
	void Draw() override;
	void Destroy() override;
	void FlipVertical(bool value);
	void FlipHorizontal(bool value);
	void SetVerticalFrames(int value);
	void SetHorizontalFrames(int value);
	void SetCurrentFrame(int value);
	void SetTotalFrames(int value);
	Sprite(Renderer *_renderer);
	virtual ~Sprite();
};

