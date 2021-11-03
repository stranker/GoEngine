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

void fragment()
{
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
	
	// Obtengo el color de mi textura principal, en mi caso una carta Pokemon.
	vec4 mainColor = texture(main_texture, UV);
	
	// Obtengo el color final haciendo un mix con mi color principal, la tabla de colores y la mascara. Por ende si la mascara es negra en el punto, va a tomar completamente el color
	// principal de mi carta. Por el contrario, si el punto en la mascara es blanco, el color final va a ser totalmente el color de mi foil.
	// Es lo mismo que mainColor.rgb  * (1 − mask) + gradient * mask.
	vec3 finalColor = mix(mainColor.rgb, gradient, mask) * light_energy;
	
	// Finalmente devuelvo el color final con el alpha de mi color principal.
	ALBEDO = vec4(finalColor, mainColor.a);
}