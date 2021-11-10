#version 330 core

struct Material {
    sampler2D albedo_texture;
    sampler2D specular_texture;
	//sampler2D normalmap_texture;
	vec3 albedo;
	float specular;
    float metallic;
	bool unshaded;
}; 

struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    float specular;
	float energy;
	bool visible;
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
	bool visible;
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
	bool visible;
};

#define MAX_POINT_LIGHTS 20
#define MAX_DIRECT_LIGHTS 2
#define MAX_SPOT_LIGHTS 20

in vec3 POSITION;
in vec2 UV;
in vec3 vNORMAL;
in mat4 CAMERA_MATRIX;
in mat4 CAMERA_INVERSE_MATRIX;
in float TIME;
uniform vec3 viewPos;
vec3 VIEW_DIR;
vec3 NORMAL;

uniform DirLight dirLights[MAX_DIRECT_LIGHTS];
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform Material material;

uniform int dirLightSize;
uniform int pointLightSize;
uniform int spotLightSize;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 materialAlbedo);
vec3 CalcPointLight(PointLight light, vec3 materialAlbedo);
vec3 CalcSpotLight(SpotLight light, vec3 materialAlbedo);

out vec4 ALBEDO;

void fragment(){};

void main()
{    
    NORMAL = normalize(vNORMAL);
	VIEW_DIR = normalize(viewPos - POSITION);
	
	fragment();
	
#ifndef CUSTOM_ALBEDO
	vec4 albedo = texture(material.albedo_texture, UV);
#else
	vec4 albedo = ALBEDO;
#endif
    
#ifndef DEFAULT_UNSHADED
	if(!material.unshaded){
		vec3 result;
		// phase 1: directional lighting
		for(int i = 0; i < dirLightSize; i++)
			result += CalcDirLight(dirLights[i], albedo.xyz);
		// phase 2: point lights
		for(int i = 0; i < pointLightSize; i++)
			result += CalcPointLight(pointLights[i], albedo.xyz);    
		// phase 3: spot light
		for(int i = 0; i < spotLightSize; i++)
			result += CalcSpotLight(spotLights[i], albedo.xyz);
		ALBEDO = albedo * vec4(result, 1.0);
	}
#endif
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 materialAlbedo)
{
	if(!light.visible){ return vec3(0.0);};
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(NORMAL, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, NORMAL);
    float spec = pow(max(dot(VIEW_DIR, reflectDir), 0.0), material.metallic * 128.0);
    // combine results
    vec3 ambient = light.ambient * materialAlbedo;
    vec3 diffuse = light.ambient * diff * materialAlbedo;
    vec3 specular = light.ambient * light.specular * spec * vec3(texture(material.specular_texture, UV));
    return (ambient + diffuse + specular)  * light.energy;
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 materialAlbedo)
{
	if(!light.visible){ return vec3(0.0);};
    vec3 lightDir = normalize(light.position - POSITION);
	vec3 halfwayDir = normalize(lightDir + VIEW_DIR);
    // diffuse shading
    float diff = max(dot(NORMAL, lightDir), 0.0);
    // specular shading
    float spec = pow(max(dot(VIEW_DIR, halfwayDir), 0.0), material.metallic * 128.0f);
    // attenuation
    float distance = length(light.position - POSITION);
    float attenuation = light.range / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * materialAlbedo;
    vec3 diffuse = light.ambient * diff * materialAlbedo;
    vec3 specular = light.ambient * light.specular * spec * vec3(texture(material.specular_texture, UV));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * light.energy;
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 materialAlbedo)
{
	if(!light.visible){ return vec3(0.0);};
    vec3 lightDir = normalize(light.position - POSITION);
	vec3 halfwayDir = normalize(lightDir + VIEW_DIR);
    // diffuse shading
    float diff = max(dot(NORMAL, lightDir), 0.0);
    // specular shading
    float spec = pow(max(dot(VIEW_DIR, halfwayDir), 0.0), material.metallic * 128.0f);
    // attenuation
    float distance = length(light.position - POSITION);
    float attenuation = light.range / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * materialAlbedo;
    vec3 diffuse = light.ambient * diff * materialAlbedo;
    vec3 specular = light.ambient * light.specular * spec * vec3(texture(material.specular_texture, UV));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * light.energy;
}