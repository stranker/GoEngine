#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

out vec3 POSITION;
out vec2 UV;
out vec3 NORMAL;
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
	
	gl_Position = projection * view * vec4(modelPos.xyz, 1.0);
}