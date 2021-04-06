#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
uniform mat4 mvp;
out vec4 ourColor; // output a color to the fragment shader

void main(){
	gl_Position = mvp * vec4(aPos, 1.0f);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}   