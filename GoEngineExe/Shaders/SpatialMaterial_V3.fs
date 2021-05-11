#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float metallic;
}; 

struct Light {
    vec3 position;  
    vec3 direction;
	
	float specular;
	float energy;
	vec3 color;	
	
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
	float range;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = vec3(1.0) * texture(material.diffuse, TexCoords).rgb;
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * texture(material.diffuse, TexCoords).rgb;  
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.metallic * 128.0);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;  
    
	// spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	ambient  *= intensity;
    diffuse  *= intensity;
    specular *= intensity;
    
    // attenuation 
    float distance = length(light.position - FragPos);
    float attenuation = light.range / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    ambient *= attenuation; 
    diffuse *= attenuation;
    specular *= attenuation;   
    
	vec3 result = (ambient + diffuse + specular) * light.energy;
    FragColor = vec4(result, 1.0);
} 