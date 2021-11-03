shader_type spatial;
uniform vec4 lineColor;
  
void fragment()
{
    ALBEDO = lineColor;
}