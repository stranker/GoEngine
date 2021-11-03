#ifndef ENGINE_3D
#pragma once
#include "Node2D.h"

class ENGINEDLL_API Sprite :
	public Node2D {
protected:
	struct UVFrame {
		Vector2 tr; // top right
		Vector2 br; // bottom right
		Vector2 bl; // bottom left
		Vector2 tl; // top left
	};
	Material* material;
	Texture* texture;
	int verticalFrames = 1;
	int horizontalFrames = 1;
	int currentFrame = 0;
	int totalFrames = 1;
	vector<UVFrame> framesRect;
	void AddFramesRect();
	Vector2 spriteSize;
	bool flipVertical = false;
	bool flipHorizontal = false;
private:
	const int draw_vertices = 6;
public:
	Vector2 GetSize() const;
	void SetTexture(const char* filePath, int vFrames, int hFrames);
	void Draw() override;
	void Destroy() override;
	void FlipVertical(bool value);
	void FlipHorizontal(bool value);
	void SetCurrentFrame(unsigned int value);
	void SetTotalFrames(int value);
	AABB GetAABB() const;
	Sprite();
	virtual ~Sprite();
};

#endif