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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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

GLuint Renderer::CreateTextureBuffer(unsigned char * data, int width, int height, int nrChannels) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return texture;
}

void Renderer::BindBuffer(GLuint bufferID, BufferType bufferType){
	glBindBuffer((GLenum)bufferType, bufferID);
}

void Renderer::BindTexture(GLuint textureBuffer) {
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
}

void Renderer::BindVertexArray(GLuint vertexArrayID) {
	glBindVertexArray(vertexArrayID);
}

void Renderer::SetAttributePointer(GLuint attributeId, size_t dataCount) {
	glVertexAttribPointer(attributeId, dataCount, GL_FLOAT, GL_FALSE, dataCount * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attributeId);
}

void Renderer::SetTextureParameters(unsigned char * data, int width, int height) {
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
