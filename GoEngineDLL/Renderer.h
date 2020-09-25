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
	bool Init();
	bool Destroy();
	GLuint CreateVertexBuffer(float *data, size_t dataSize);
	void BindBuffer(GLuint attributeId, GLuint bufferID, size_t dataCount);
	void SetClearColor(float r, float g, float b, float a);
	void SetClearColor(Color color);
	void ClearScreen();
	void SwapBuffers();
	void DisableBuffer(size_t attributeID);
	void DeleteBuffer(GLuint bufferID);
	void Draw(Primitive _primitive, int vertexCount);
	Camera* GetCamera();
	Renderer(Window* _window);
	virtual ~Renderer();
};

