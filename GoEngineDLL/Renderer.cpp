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
	return true;
}

bool Renderer::Destroy(){
	cout << "Renderer Destroy" << endl;
	if (camera) {
		delete camera;
	}
	return true;
}

GLuint Renderer::CreateVertexBuffer(float *data, size_t dataSize, BufferType bufferType) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

GLuint Renderer::CreateVertexBuffer(unsigned int * data, size_t dataSize, BufferType bufferType) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

void Renderer::BindBuffer(GLuint bufferID, BufferType bufferType){
	glBindBuffer((GLenum)bufferType, bufferID);
}

void Renderer::BindVertexArray(GLuint vertexArrayID) {
	glBindVertexArray(vertexArrayID);
}

void Renderer::SetAttributePointer(GLuint attributeId, size_t dataCount) {
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

void Renderer::DrawElements(Primitive _primitive, int vertexCount) {
	glDrawElements((GLenum)_primitive, vertexCount, GL_UNSIGNED_INT, 0);
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
