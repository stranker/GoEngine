#pragma once
#include "Entity2D.h"
#include "TextureMaterial.h"

class ENGINEDLL_API Sprite :
	public Entity2D {
protected:
	unsigned int uvBuffer;
	unsigned int textureBuffer;
private:
	struct UVFrame {
		Vector2 tr;
		Vector2 br;
		Vector2 bl;
		Vector2 tl;
	};
	TextureMaterial *texture;
	bool flipVertical = false;
	bool flipHorizontal = false;
	int verticalFrames = 1;
	int horizontalFrames = 1;
	int currentFrame = 0;
	int totalFrames = 1;
	vector<UVFrame> framesRect;
	Vector2 spriteSize;
	void AddFramesRect();
public:
	Vector2 GetSize() const;
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

