#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 OurColor;

uniform mat4 mvp;
uniform vec2 offset;
uniform vec4 color;

void main()
{
    float scale = 2.0f;
    TexCoord = aTexCoord;
    OurColor = color;
	gl_Position = mvp * vec4((aPos * scale) + vec3(offset,0.0), 1.0);
}