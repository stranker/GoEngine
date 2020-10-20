#version 330 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform bool flipVertical;
uniform bool flipHorizontal;
uniform vec4 selfModulate;
uniform sampler2D ourTexture;

void main(){
	float finalCoord_x = flipVertical ? 1. - TexCoord.x : TexCoord.x;
	float finalCoord_y = flipHorizontal ? 1. - TexCoord.y : TexCoord.y;
    FragColor = texture(ourTexture, vec2(finalCoord_x, finalCoord_y)) * selfModulate;
}