#version 330 core

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

out vec4 FragColor;

void main()
{    
    vec3 position = texture(gPosition, fsUv).xyz;
    vec3 albedo = texture(gAlbedo, fsUv).xyz;
    vec3 normal = normalize(texture(gNormal, fsUv).xyz);
	albedo = vec3(1.0, 0.0, 0.0);
	FragColor = vec4(albedo,1.0);
	
}