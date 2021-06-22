#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D texture_diffuse;
    vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    float metallic;
	bool hasTexture;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    float specular;
	float energy;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    float specular;
	float energy;
	float range;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    float specular;
	float range;
	float energy;
};

#define MAX_POINT_LIGHTS 20
#define MAX_DIRECT_LIGHTS 2
#define MAX_SPOT_LIGHTS 20

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform DirLight dirLights[MAX_DIRECT_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;

uniform int dirLightSize;
uniform int pointLightSize;
uniform int spotLightSize;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // phase 1: directional lighting
    vec3 result;
	for(int i = 0; i < dirLightSize; i++)
		result += CalcDirLight(dirLights[i], norm, viewDir);
    // phase 2: point lights
    for(int i = 0; i < pointLightSize; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
    // phase 3: spot light
	for(int i = 0; i < spotLightSize; i++)
		result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);    
    
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.metallic * 128.0);
    // combine results
	vec3 textureDiffuse = vec3(1.0);
	if(material.hasTexture){
		textureDiffuse = vec3(texture(material.texture_diffuse, TexCoords));
	}
	vec3 ambient = (material.hasTexture ? textureDiffuse : material.ambient) * light.ambient;
    vec3 diffuse = material.diffuse * diff * textureDiffuse;
    vec3 specular = material.specular * light.specular * spec * textureDiffuse;
    return (ambient + diffuse + specular) * light.energy;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.metallic * 128.0f);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = light.range / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
	vec3 textureDiffuse = vec3(1.0);
	if(material.hasTexture){
		textureDiffuse = vec3(texture(material.texture_diffuse, TexCoords));
	}
	vec3 ambient = (material.hasTexture ? textureDiffuse : material.ambient) * light.ambient;
    vec3 diffuse = material.diffuse * diff * textureDiffuse;
    vec3 specular = material.specular * light.specular * spec * textureDiffuse;
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.energy;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.metallic * 128.0f);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = light.range / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
	vec3 textureDiffuse = vec3(1.0);
	if(material.hasTexture){
		textureDiffuse = vec3(texture(material.texture_diffuse, TexCoords));
	}
	vec3 ambient = (material.hasTexture ? textureDiffuse : material.ambient) * light.ambient;
    vec3 diffuse = material.diffuse * diff * textureDiffuse;
    vec3 specular = material.specular * light.specular * spec * textureDiffuse;
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * light.energy;
}