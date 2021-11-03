#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

uniform mat4 view;

out vec2 UV;

void main()
{
    UV = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}