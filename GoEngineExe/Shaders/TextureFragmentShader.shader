#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

uniform bool flipVertical;
uniform bool flipHorizontal;
uniform vec4 selfModulate; // color que se aplica a la textura
uniform sampler2D sprite;

void main(){
	float finalCoord_x = flipVertical ? 1. - TexCoord.x : TexCoord.x;
	float finalCoord_y = flipHorizontal ? 1. - TexCoord.y : TexCoord.y;
    FragColor = texture(sprite, vec2(finalCoord_x, finalCoord_y)) * selfModulate;
}