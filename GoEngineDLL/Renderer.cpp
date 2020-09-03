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

void Renderer::BindBuffer(GLuint vertexBuffer, uint8_t size){
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
		size,                  // tamaño
		GL_FLOAT,           // tipo
		GL_FALSE,           // normalizado?
		0,                    // Paso
		(void*)0            // desfase del buffer
	);
}

void Renderer::CreateTriangleBuffer(){
	float triangle_vertex_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	unsigned int vertexBuffer = CreateVertexBuffer(triangle_vertex_data, sizeof(triangle_vertex_data));
	BindBuffer(vertexBuffer, 3);
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
