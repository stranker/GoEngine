#include "Light.h"

Light::Light(Renderer* _renderer) : Entity3D(_renderer){
    float position_vertex_data[] = {
     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,

     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f, -0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,

      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,

     -0.5f, -0.5f, -0.5f,
      0.5f, -0.5f, -0.5f,
      0.5f, -0.5f,  0.5f,
      0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f,  0.5f,
     -0.5f, -0.5f, -0.5f,

     -0.5f,  0.5f, -0.5f,
      0.5f,  0.5f, -0.5f,
      0.5f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f,  0.5f,
     -0.5f,  0.5f, -0.5f,
    };
    CreateVertexArrayID(); //crea el VAO
    CreateVertexData(position_vertex_data, sizeof(position_vertex_data), 3, Renderer::ARRAY_BUFFER, 0); // VBO
    BindVertexObjects(); // Bindeo VAO
    primitive = Renderer::TRIANGLES;
    material = new Material();
    material->LoadShaders("Shaders/SimpleVertex3dShader.shader", "Shaders/SimpleFragmentShader.shader");
    cout << "Creating Light" << endl;
	SetPosition(Vector3(1.2f, 1.0f, 2.0f));
}

Light::~Light() {
}
