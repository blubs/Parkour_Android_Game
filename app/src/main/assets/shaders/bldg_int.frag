precision mediump float;

varying vec2 v_uv_1;
varying vec2 v_uv_2;

varying vec3 cam_dir_tanspace;
varying vec3 dirlight_dir_tanspace;
varying vec3 ref_dir;

uniform sampler2D tex_nor;
uniform sampler2D tex_diff;
uniform sampler2D tex_lm;
uniform samplerCube cube_map;


//TODO: misc color map with specular, transparent, and reflective values
//TODO: cubemap reflections

void main()
{
	//gl_FragColor = color*0.01 + v_color*0.01 + vec4( v_uv_1.x , v_uv_1.y , v_uv_2.x , v_uv_2.y );
	//Getting fragment normal
	//Modulating the normal map strength (lerping between unmodified normal and normal specified by normal map by strength amount)
	const float normal_map_strength = 0.3;
	vec3 normal_dir = normalize(mix(vec3(0,0,1),(texture2D(tex_nor,v_uv_1).rgb * 2.0 - 1.0),normal_map_strength));

	//Light Calculation
	//float diffuse = clamp(dot(normal_dir,dirlight_dir_tanspace),0.0,1.0);

	//Specular shading
	const float shininess = 5.0;//ranged 1-20
	float specular = pow(clamp(dot(reflect(-dirlight_dir_tanspace,normal_dir),cam_dir_tanspace),0.0,1.0),shininess);

	//Rim light shading
	//const float rim_power = 3.0;//ranged 0.1-10
	//float rim = 1.0 - clamp(dot(cam_dir_tanspace,normal_dir),0.0,1.0);
	//rim = pow(rim,rim_power);

	const float ambient_light = 0.1;

	//Lightmaps are currently monochromatic
	float lightmap_brightness = texture2D(tex_lm,v_uv_2).x;
	//float light_power = ambient_light + diffuse + specular + rim;
	//float light_power = ambient_light + 0.7*specular + rim + lightmap_brightness;
	float light_power = ambient_light + 0.7*specular + lightmap_brightness;

	vec3 color = texture2D(tex_diff,v_uv_1).rgb;
	gl_FragColor = vec4(color*light_power, 1.0) * 0.01 + textureCube(cube_map,ref_dir);
	//gl_FragColor = vec4(1.0,0.0,0.0,1.0);

}