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
	return true;
}

GLuint Renderer::CreateVertexBuffer(float *data, size_t dataSize) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	return vertexBuffer;
}

void Renderer::BindBuffer(GLuint attributeId, uint8_t dataCount, uint8_t dataSize, uint8_t offset){
	glVertexAttribPointer(attributeId, dataCount, GL_FLOAT, GL_FALSE, dataSize * sizeof(float), (void*)(offset * sizeof(float)));
	glEnableVertexAttribArray(attributeId);
}

GLuint Renderer::CreateTriangleBuffer(){
	float triangle_vertex_data[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f,   // top 
	};
	GLuint vertexBuffer = CreateVertexBuffer(triangle_vertex_data, sizeof(triangle_vertex_data));
	// Positions
	BindBuffer(0, 3, 7, 0);
	// Colors
	BindBuffer(1, 4, 7, 3);
	return vertexBuffer;
}

void Renderer::SetClearColor(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
}

void Renderer::ClearScreen(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SwapBuffers(){
	glfwSwapBuffers(window->GetWindowPtr());
}

void Renderer::DrawBuffer(uint8_t vertexCount){
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

Renderer::Renderer(Window* _window){
	window = _window;
}


Renderer::~Renderer(){
}
