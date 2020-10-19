#pragma once

#include "Window.h"
#include "Color.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class ENGINEDLL_API Renderer
{
protected:
	Window* window;
	Camera* camera;
	GLuint vertexArrayId;
public:
	enum Primitive {
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005,
	};
	enum BufferType {
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER
	};
	bool Init();
	bool Destroy();
	GLuint CreateVertexBuffer(float *data, size_t dataSize, BufferType bufferType);
	GLuint CreateVertexBuffer(unsigned int *data, size_t dataSize, BufferType bufferType);
	GLuint CreateTextureBuffer(unsigned char * data, int width, int height, int nrChannels);
	void BindBuffer(GLuint bufferID, BufferType bufferType);
	void BindTexture(GLuint textureBuffer);
	void BindVertexArray(GLuint vertexArrayID);
	void SetAttributePointer(GLuint attributeId, size_t dataCount);
	void SetTextureParameters(unsigned char* data, int width, int height);
	void SetClearColor(float r, float g, float b, float a);
	void SetClearColor(Color color);
	void ClearScreen();
	void SwapBuffers();
	void DisableBuffer(size_t attributeID);
	void DeleteBuffer(GLuint bufferID);
	void Draw(Primitive _primitive, int vertexCount);
	void DrawElements(Primitive _primitive, int vertexCount);
	Camera* GetCamera();
	Renderer(Window* _window);
	virtual ~Renderer();
};

