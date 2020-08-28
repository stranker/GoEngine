#include "BaseGame.h"

bool BaseGame::free()
{
	if (window){
		window->free();
	}
	return true;
}

// Identificar el vertex buffer
GLuint vertexbuffer;
void BaseGame::init(){
	window->init();

	//VAO
	GLuint VertexArrayID;
	if (glewInit() == GLEW_OK) {		glGenVertexArrays(1, (&VertexArrayID));		glBindVertexArray(VertexArrayID);	}
	//

	//Vectores
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
	//

	//Creando un buffer
	
	// Generar un buffer, poner el resultado en el vertexbuffer que acabamos de crear
	glGenBuffers(1, &vertexbuffer);
	// Los siguientes comandos le darán características especiales al 'vertexbuffer' 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Darle nuestros vértices a  OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	//
}

void BaseGame::loop(){
	while (!window->should_close()){
		window->set_clear_color(0.5f, 0.0f, 0.5f, 1.0f);
		window->clear_color();

		//Dibujando el triangulo
		// 1rst attribute buffer : vértices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
			3,                  // tamaño
			GL_FLOAT,           // tipo
			GL_FALSE,           // normalizado?
			0,                    // Paso
			(void*)0            // desfase del buffer
		);
		// Dibujar el triángulo !
		glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
		glDisableVertexAttribArray(0);
		//

		window->swap_buffers();
		window->pool_events();

		
	}
}

BaseGame::BaseGame(int _screen_width, int _screen_height, const char * _screen_title){
	window = new Window(_screen_width, _screen_height, _screen_title);
}

BaseGame::~BaseGame(){
}
