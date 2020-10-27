#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 mvp;
uniform int horizontalFrames;
uniform int verticalFrames;
uniform int currentFrame;

out vec4 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0f);
	ourColor = aColor;
	TexCoord.x = (mod(currentFrame, verticalFrames) + aTexCoord.x) * (1.0 / verticalFrames);
	TexCoord.y = (floor(currentFrame / verticalFrames) + aTexCoord.y) * (1.0 / horizontalFrames);
}