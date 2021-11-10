shader_type spatial;

uniform sampler2D main_texture;
uniform sampler2D normal_texture;
uniform sampler2D noise_texture;
uniform sampler2D gradient_texture;
uniform sampler2D mask_texture;
uniform float noise_strength = 1.0;
uniform float mask_opacity = 1.0;
uniform float light_energy = 1.0;
uniform float time_mul = 0.1;
const vec3 normal_direct = vec3(0.5,0.5,1);

uniform float shine_width;
uniform float shine_angle;
uniform float shine_velocity;

uniform float shine_progress;

uniform float shine_2_width;
uniform float shine_2_angle;
uniform float shine_2_velocity;

void fragment()
{
	// Shine 1
	// Primero calculo un float que va desde -1 a 1 utilizando el coseno del TIME, que es el tiempo que transcurre en el engine, y lo multiplico por la velocidad
	// del shine.
	float shine_sweep = cos(TIME * shine_velocity);
	
	// Luego calculo la distancia del pixel actual hacia la linea principal. Esto va a determinar posteriormente la cantidad de shine que va a tener el pixel
	float uv_distance_line = abs((UV.x * cos(radians(shine_angle)) - shine_progress) - (UV.y * sin(radians(shine_angle)) + shine_progress));
	
	// Divido la distancia obtenida por el tamanio del shine y resto esto a 1. Luego obtengo el maximo de este resultado con 0.0
	float shine = max(1.0 - (uv_distance_line / shine_width),0.0);
	
	float shine_2_sweep = cos(TIME * shine_2_velocity) * 2.0 - 1.0;
	float uv_distance_line_2 = abs((UV.x * cos(radians(shine_2_angle)) - shine_2_sweep) - (UV.y  * sin(radians(shine_2_angle)) + shine_2_sweep));
	float shine_2 = max(1.0 - (uv_distance_line_2 / shine_2_width),0.0);
	
	//NORMAL = 
	//NORMAL = normalize(NORMAL * 2.0 - 1.0);
	
	// Obtengo un vector3 con la textura del noise multiplicado por la fuerza del noise. Me devuelve un vector en la escala de grises
	vec3 noise = (texture(noise_texture, UV).xyz) * noise_strength;

	// Primero normalizo la suma entre mi normal y mi vector noise. Por ej: Si mi normal es (0,0,1) y el ruido en ese punto es blanco (1,1,1)
	// La suma da (1,1,2) y su normalizado da (0.408248,0.408248,0.816497). Luego hago producto punto con el vector direccion y con eso
	// hago el maximo con 0 para evitar valores negativos.
	// Luego resto 1.0 con el resultado total de la cuenta anterior para obtener una magnitud inversa a la de la vista.
	float inverseView = 1.0 - max(dot(normalize(NORMAL + noise), VIEW_DIR), 0.0);
	
	// Con este valor ahora puedo obtener un color de la textura del gradiente como haciendo un "barrido", ya que solo se  cambia el valor de X.
	vec2 gradientUV = vec2(inverseView + TIME * time_mul, 0.0);
	vec3 gradient = texture(gradient_texture, gradientUV).rgb;
	
	// Luego saco un vector3 con la textura de la mascara. Los valores son 2: Blanco o Negro. (1,1,1) y (0,0,0)
	vec3 mask = texture(mask_texture, UV).rgb * mask_opacity;
	
	NORMAL = mask == vec3(0.0) ? normal_direct : normalize(texture(normal_texture, UV).rgb);
	
	// Obtengo el color de mi textura principal, en mi caso una carta Pokemon.
	vec4 mainColor = texture(main_texture, UV);
	
	// Obtengo el color final haciendo un mix con mi color principal, la tabla de colores y la mascara. Por ende si la mascara es negra en el punto, va a tomar completamente el color
	// principal de mi carta. Por el contrario, si el punto en la mascara es blanco, el color final va a ser totalmente el color de mi foil.
	// Es lo mismo que mainColor.rgb  * (1 − mask) + gradient * mask.
	vec3 finalColor = mix(mainColor.rgb, gradient, mask) * light_energy;
	
	finalColor += shine + shine_2;
	
	// Finalmente devuelvo el color final con el alpha de mi color principal.
	ALBEDO = vec4(finalColor, mainColor.a);
}