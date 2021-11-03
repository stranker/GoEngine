#pragma once
#include "Utils.h"
#include "GlInclude.h"
#include "TextureImporter.h"

class ENGINEDLL_API FrameBuffer {
public:
	enum BufferTextureType {
		GBUFFER_TEXTURE_TYPE_POSITION,
		GBUFFER_TEXTURE_TYPE_NORMAL,
		GBUFFER_TEXTURE_TYPE_ALBEDO,
		GBUFFER_NUM_TEXTURES
	};
private:
	Vector2 windowsSize;
	unsigned int fbo;
	Texture* texture;
	unsigned int depth;
	Texture* textures[GBUFFER_NUM_TEXTURES];
	bool multipleTextures = false;
	GLuint fullscreenQuad_VAO;
	GLuint fullscreenQuad_VBO;
public:
	void Init();
	void InitGBuffer();
	void Bind();
	void BindWriting();
	void BindReading();
	void Unbind();
	void DeleteBuffers();
	void BindTexture();
	void BindTextures();
	bool IsComplete();
	void SetReadBuffer(BufferTextureType type);
	void ShowTexture(BufferTextureType type, int width, int height, int x, int y);
	void DrawToScreen();
	Texture* GetTexture(BufferTextureType type) const;
	Texture* GetTexture() const;
	FrameBuffer();
	~FrameBuffer();
};
