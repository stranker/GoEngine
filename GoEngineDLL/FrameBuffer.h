#pragma once
#include "Utils.h"

class ENGINEDLL_API FrameBuffer {
private:
	Vector2 windowsSize;
	unsigned int fbo;
	unsigned int rbo;
	unsigned int depth;
	unsigned int stencil;
	unsigned int texture;
public:
	void Init();
	void Bind();
	void Unbind();
	void DeleteBuffers();
	bool FrameBufferComplete();
	FrameBuffer();
	~FrameBuffer();
};

