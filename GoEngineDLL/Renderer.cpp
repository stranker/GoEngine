#include "Renderer.h"
#include "GlInclude.h"
#include "Window.h"

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
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

bool Renderer::Destroy(){
	cout << "Renderer Destroy" << endl;
	if (firstCamera){
		firstCamera->Destroy();
		delete firstCamera;
		firstCamera = NULL;
	}
	if (camera) {
		camera->Destroy();
		delete camera;
		camera = NULL;
	}
	return true;
}

unsigned int Renderer::CreateVertexBuffer(float *data, size_t dataSize, BufferType bufferType) {
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

unsigned int Renderer::CreateVertexBuffer(unsigned int * data, size_t dataSize, BufferType bufferType) {
	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer((GLenum)bufferType, vertexBuffer);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

unsigned int Renderer::CreateTextureBuffer(unsigned char * data, int width, int height, int nrChannels) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return texture;
}

void Renderer::UpdateVertexBuffer(unsigned int vbo, float * data, size_t dataSize, BufferType bufferType) {
	glGenBuffers(1, &vbo);
	glBindBuffer((GLenum)bufferType, vbo);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
}

void Renderer::UpdateVertexBuffer(unsigned int vbo, unsigned int * data, size_t dataSize, BufferType bufferType) {
	glGenBuffers(1, &vbo);
	glBindBuffer((GLenum)bufferType, vbo);
	glBufferData((GLenum)bufferType, dataSize, data, GL_STATIC_DRAW);
}

unsigned int Renderer::CreateVertexArrayID() {
	unsigned int vao;
	glGenVertexArrays(1, (&vao));
	glBindVertexArray(vao);
	return vao;
}

void Renderer::BindBuffer(unsigned int bufferID, BufferType bufferType){
	glBindBuffer((GLenum)bufferType, bufferID);
}

void Renderer::SetAttributePointer(unsigned int attributeId, size_t dataCount) {
	glVertexAttribPointer(attributeId, dataCount, GL_FLOAT, GL_FALSE, dataCount * sizeof(float), (void*)0);
	glEnableVertexAttribArray(attributeId);
}

void Renderer::BindBufferWithAttribute(unsigned int bufferID, BufferType bufferType, int attributeID, unsigned int vertexCount) {
	BindBuffer(bufferID, bufferType);
	if (attributeID != -1) { // Es un buffer que debo setearle atributos? /* NOTA: Index buffer no necesita setear atributos */
		SetAttributePointer(attributeID, vertexCount);
	}
}

void Renderer::BindVertexData(VertexData vertexData) {
	BindBufferWithAttribute(vertexData.vbo, vertexData.bufferType, vertexData.attributeID, vertexData.dataCount);
}

void Renderer::BindTexture(unsigned int textureBuffer) {
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
}

void Renderer::BindVertexArray(unsigned int vertexArrayID) {
	glBindVertexArray(vertexArrayID);
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

void Renderer::SetClearColor(Color color) {
	glClearColor(color.r, color.g, color.b, color.a);
}

void Renderer::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers(){
	glfwSwapBuffers((GLFWwindow*)window->GetWindowPtr());
}

void Renderer::DisableBuffer(size_t attributeID) {
	glDisableVertexAttribArray(attributeID);
}

void Renderer::DeleteBuffer(unsigned int _buffer) {
	glDeleteBuffers(1, &_buffer);
}

void Renderer::Draw(Primitive _primitive, int vertexCount) {
	glDrawArrays((GLenum)_primitive, 0, vertexCount);
}

void Renderer::DrawElements(Primitive _primitive, int vertexCount) {
	glDrawElements((GLenum)_primitive, vertexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::EnableClientState() {
	glEnableClientState(GL_VERTEX_ARRAY);
}

void Renderer::DisableClientState() {
	glDisableClientState(GL_VERTEX_ARRAY);
}
Renderer* Renderer::singleton = NULL;

Renderer* Renderer::GetSingleton() {
	return singleton;
}

void Renderer::Draw(unsigned int vao, Primitive _primitive, int vertexCount, bool elementDraw) {
	BindVertexArray(vao);
	if (elementDraw){
		DrawElements(_primitive, vertexCount);
	}
	else{
		Draw(_primitive, vertexCount);
	}
}

Camera * Renderer::GetCamera() {
	return camera;
}

void Renderer::SetCurrentCamera(Camera* _camera){
	camera = _camera;
}

Renderer::Renderer(Window* _window){
	window = _window;
	firstCamera = new Camera(window->GetWidth(), window->GetHeight());
	camera = firstCamera;
	singleton = this;
}

Renderer::~Renderer(){
}
