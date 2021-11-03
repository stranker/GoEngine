#version 330 core

in vec2 fsUv;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    float specular;
	float energy;
};

#define MAX_DIRECT_LIGHTS 2
uniform DirLight dirLights[MAX_DIRECT_LIGHTS];
uniform int dirLightSize;

in vec3 viewPos;
in vec2 screenSize;

out vec4 FragColor;

vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 albedo);

void main()
{
    vec3 position = texture(gPosition, fsUv).xyz;
    vec3 albedo = texture(gAlbedo, fsUv).xyz;
    vec3 normal = normalize(texture(gNormal, fsUv).xyz);
	
	vec3 viewDir = normalize(viewPos - position);
	
	vec3 l = normalize(vec3(-0.7, 0.3, 0.1));
	vec3 v = normalize(viewDir);
	vec3 h = normalize(l + v);
	
	vec3 color = 0.7 * albedo.xyz * max(0.0, dot(normal.xyz, l)) + 0.4 * pow(max(0.0, dot(h, normal)), 32.0) + 0.2 * albedo.xyz;
	
	vec3 result = vec3(0.0);
	for(int i = 0; i < dirLightSize; i++)
		result += CalcDirectionalLight(dirLights[i], normal, viewDir, albedo);
	FragColor = vec4(result, 1.0);
}

vec3 CalcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 albedo)
{
    vec3 lightDir = normalize(-light.direction);
	// diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    // combine results
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = diff * albedo * 0.7  * light.energy;
    vec3 specular = vec3(light.specular) * spec;
    return (ambient + diffuse + specular);
}