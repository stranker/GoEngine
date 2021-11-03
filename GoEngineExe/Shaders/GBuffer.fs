#version 330 core
layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec3 gAlbedo;

in vec2 UV;
in vec3 POSITION;
in vec3 NORMAL;

uniform sampler2D texture_diffuse;

void main()
{    
    // store the fragment position vector in the first gbuffer texture
    gPosition = POSITION;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(NORMAL);
    // and the diffuse per-fragment color
    gAlbedo = texture(texture_diffuse, UV).xyz;
}