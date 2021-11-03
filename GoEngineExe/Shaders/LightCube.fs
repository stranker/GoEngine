shader_type spatial;

#define DEFAULT_UNSHADED
uniform vec3 lightColor;

void fragment()
{
    ALBEDO = vec4(lightColor, 1.0);
}