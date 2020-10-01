#include "Renderer.h"

bool Renderer::Init(){
	cout << "Renderer Init" << endl;
	if (!window) {
		cout << "Window ptr not created" << endl;
		return false;
	}
	if (glewInit() != GLEW_OK){
		cout << "Failed to init Glew" << endl;
		return false;
	}
	glGenVertexArrays(1, (&vertexArrayId));
	glBindVertexArray(vertexArrayId);
	return true;
}

bool Renderer::Destroy(){
	cout << "Renderer Destroy" << endl;
	if (camera) {
		delete camera;
	}
	return true;
}

GLuint Renderer::CreateVertexBuffer(float *data, size_t dataSize) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

void Renderer::BindBuffer(GLuint attributeId, GLuint bufferID,  size_t dataCount){
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);						//stride
	glVertexAttribPointer(attributeId, dataCount, GL_FLOAT, GL_FALSE, dataCount * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attributeId);
}

void Renderer::SetClearColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void Renderer::SetClearColor(Color color) {
	SetClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers(){
	glfwSwapBuffers(window->GetWindowPtr());
}

void Renderer::DisableBuffer(size_t attributeID) {
	glDisableVertexAttribArray(attributeID);
}

void Renderer::DeleteBuffer(GLuint _buffer) {
	glDeleteBuffers(1, &_buffer);
}

void Renderer::Draw(Primitive _primitive, int vertexCount) {
	glDrawArrays((GLenum)_primitive, 0, vertexCount);
}

Camera * Renderer::GetCamera() {
	return camera;
}

Renderer::Renderer(Window* _window){
	window = _window;
	camera = new Camera(window->GetWidth(), window->GetHeight());
}

Renderer::~Renderer(){
}
