#version 330 core
uniform sampler2D main_texture;
uniform sampler2D normal_texture;
uniform sampler2D noise_texture;
uniform sampler2D foil_texture;
uniform sampler2D mask_texture;
uniform float noise_strength = 1.0;
uniform float mask_opacity = 1.0;
uniform float light_energy = 1.0;
uniform float time_mul = 0.1;
const vec3 normal_direct = vec3(0.5,0.5,1);

vec3 VIEW;
in vec3 POSITION;
in vec2 UV;
in vec3 NORMAL;
in vec3 TANGENT;
in vec3 BITANGENT;
in mat3 TBN;
in mat4 CAMERA_MATRIX;
in mat4 CAMERA_INVERSE_MATRIX;
in float TIME;

uniform vec3 viewPos;

out vec4 FragColor;

void main(){
	// Obtengo un vector3 con la textura del noise multiplicado por la fuerza del noise. Me devuelve un vector en la escala de grises
	vec3 noise = (texture(noise_texture, UV).xyz) * noise_strength;
	
	// Normalizo el NORMAL del vertex shader
	vec3 norm = normalize(NORMAL);
	// view dir
	VIEW = normalize(mat3(CAMERA_INVERSE_MATRIX) * normalize(POSITION - viewPos).xyz);
	
	// Primero normalizo la suma entre mi normal y mi vector noise. Por ej: Si mi normal es (0,0,1) y el ruido en ese punto es blanco (1,1,1)
	// La suma da (1,1,2) y su normalizado da (0.408248,0.408248,0.816497). Luego hago producto punto con el vector direccion y con eso hago el maximo con 0 para evitar negativos.
	// Luego resto 1.0 con el resultado total de la cuenta anterior para obtener una magnitud inversa a la de la vista.
	float inverseView = 1.0 - max(dot(normalize(norm + noise), VIEW), 0.0);
	
	// Con este valor ahora puedo obtener un color de la textura del foil como haciendo un "barrido", ya que solo se  cambia el valor de X.
	vec2 tableUV = vec2(inverseView + TIME * time_mul, 0.0);
	vec3 tableColor = texture(foil_texture, tableUV).rgb;
	
	// Luego saco un vector3 con la textura de la mascara. Los valores son 2: Blanco o Negro. (1,1,1) y (0,0,0)
	vec3 mask = texture(mask_texture, UV).rgb * mask_opacity;
	
	// Calculo el normal mapping
	// obtain normal from normal map in range [0,1]
    // vec3 normal = texture(normal_texture, UV).rgb;
    // // transform normal vector to range [-1,1]
    // normal = normalize(normal * 2.0 - 1.0);
	
	//NORMALMAP = mask.rgb == vec3(0.0) ? normal_direct : normalize((texture(normal_texture,UV).rgb));
	// Obtengo el color de mi textura principal, en mi caso una carta Pokemon.
	vec4 mainColor = texture(main_texture, UV);
	
	// Obtengo el color final haciendo un mix con mi color principal, la tabla de colores y la mascara. Por ende si la mascara es negra en el punto, va a tomar completamente el color
	// principal de mi carta. Por el contrario, si el punto en la mascara es blanco, el color final va a ser totalmente el color de mi foil.
	// Es lo mismo que mainColor.rgb  * (1 − mask) + tableColor * mask.
	vec3 finalColor = mix(mainColor.rgb, tableColor, mask) * light_energy;
	
	// Finalmente devuelvo el color final con el alpha de mi color principal.
	FragColor = vec4(finalColor, mainColor.a);
}