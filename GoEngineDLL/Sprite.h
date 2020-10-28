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
	vector<Rect2> framesRect;
	Vector2 spriteSize;
	void AddFramesRect();
public:
	Vector2 GetSize();
	void SetTexture(const char* filePath, ImageType imageType, int vFrames, int hFrames);
	TextureMaterial *GetTexture();
	void SetUVVertex(float *data, int dataSize);
	void Draw() override;
	void Destroy() override;
	void FlipVertical(bool value);
	void FlipHorizontal(bool value);
	void SetCurrentFrame(unsigned int value);
	void SetTotalFrames(int value);
	Sprite(Renderer *_renderer);
	virtual ~Sprite();
};

