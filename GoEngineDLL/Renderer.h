#pragma once
#include "Camera.h"

class Window;

using namespace std;

class ENGINEDLL_API Renderer
{
protected:
	Window* window;
	Camera* camera;
	unsigned int vertexArrayId;
public:
	enum Primitive {
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005,
	};
	enum BufferType {
		ARRAY_BUFFER = 0x8892,
		ELEMENT_BUFFER = 0x8893
	};
	bool Init();
	bool Destroy();
	unsigned int CreateVertexBuffer(float *data, size_t dataSize, BufferType bufferType);
	unsigned int CreateVertexBuffer(unsigned int *data, size_t dataSize, BufferType bufferType);
	unsigned int CreateTextureBuffer(unsigned char * data, int width, int height, int nrChannels);
	unsigned int CreateVertexArrayID();
	void BindBuffer(unsigned int bufferID, BufferType bufferType);
	void BindTexture(unsigned int textureBuffer);
	void BindVertexArray(unsigned int vertexArrayID);
	void SetAttributePointer(unsigned int attributeId, size_t dataCount);
	void SetTextureParameters(unsigned char* data, int width, int height);
	void SetClearColor(float r, float g, float b, float a);
	void SetClearColor(Color color);
	void ClearScreen();
	void SwapBuffers();
	void DisableBuffer(size_t attributeID);
	void DeleteBuffer(unsigned int bufferID);
	void Draw(Primitive _primitive, int vertexCount);
	void DrawElements(Primitive _primitive, int vertexCount);
	Camera* GetCamera();
	Renderer(Window* _window);
	virtual ~Renderer();
};

