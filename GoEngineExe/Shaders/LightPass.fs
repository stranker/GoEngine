#version 330 core
out vec4 FragColor;

uniform sampler2D gAlbedo;

in vec3 viewPos;
in vec3 POSITION;
in vec3 NORMAL;
in vec2 UV;

void main()
{
    vec3 albedo = texture(gAlbedo, UV).xyz;
    FragColor = vec4(albedo, 1.0);
}