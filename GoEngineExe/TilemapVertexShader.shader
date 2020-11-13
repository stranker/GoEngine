#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec4 OurColor;

uniform mat4 mvp;
uniform int tileRows;
uniform int tileColumns;
uniform int tileId;
uniform vec2 offset;

void main()
{
	gl_Position = mvp * vec4(aPos + vec3(offset,0.0), 1.0);
	OurColor = aColor;
	TexCoord.x = (mod(tileId, tileColumns) + aTexCoord.x) * (1.0 / tileColumns);
	TexCoord.y = (floor(tileId / tileColumns) + aTexCoord.y) * (1.0 / tileRows);
}