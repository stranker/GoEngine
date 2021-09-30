#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

out vec3 POSITION;
out vec2 UV;
out vec3 NORMAL;
out vec3 TANGENT;
out vec3 BITANGENT;
out mat3 TBN;
out mat4 CAMERA_MATRIX;
out mat4 CAMERA_INVERSE_MATRIX;
out float TIME;

void main(void)
{
	CAMERA_MATRIX = view;
	CAMERA_INVERSE_MATRIX = inverse(view);
	
	mat4 MODEL_VIEW = CAMERA_INVERSE_MATRIX * model;
		
	vec4 modelPos = model * vec4(aPos, 1.0);
	
	POSITION = modelPos.xyz;
	NORMAL = mat3(transpose(inverse(MODEL_VIEW))) * aNormal;
    UV = aTexCoords;
	
	TIME = time;
	
	TANGENT = normalize((MODEL_VIEW * vec4(aTangent,1.0)).xyz);
    BITANGENT = normalize((MODEL_VIEW * vec4(aBitangent,1.0)).xyz);
    TBN = transpose(mat3(TANGENT, BITANGENT, NORMAL));
	
	gl_Position = projection * view * vec4(modelPos.xyz, 1.0);
}