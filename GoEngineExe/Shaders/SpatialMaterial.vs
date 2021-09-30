#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 POSITION;
out vec3 NORMAL;
out vec2 UV;
out vec3 VIEW;

void main()
{
	vec4 modelPos = model * vec4(aPos, 1.0);
	vec3 viewPos = vec3(view * modelPos);
	
	POSITION = modelPos.xyz;
	NORMAL = mat3(transpose(inverse(model))) * aNormal;
    UV = aTexCoords;
	VIEW = normalize(viewPos);
	
	gl_Position = projection * view * vec4(POSITION, 1.0);
}