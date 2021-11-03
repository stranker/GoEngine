shader_type spatial;

#define DEFAULT_UNSHADED
uniform vec4 lineColor;

void fragment()
{
    ALBEDO = lineColor;
}