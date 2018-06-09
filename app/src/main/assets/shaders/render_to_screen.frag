precision mediump float;

varying vec2 uv;

uniform sampler2D tex_diff;

//uniform float view_width;
//uniform float view_height;

uniform float screen_desaturation;


void main()
{
//	vec2 uv = vec2(gl_FragCoord.x / view_width, gl_FragCoord.y/view_height);
	vec3 screen_color = texture2D(tex_diff,uv).rgb;


	//The following code is for desaturating the screen (but only the gb components)

	//Desaturation according to luma
	//float luma = 0.3 * screen_color.r + 0.6 * screen_color.g + 0.1 * screen_color.b;
	//screen_color.r += screen_desaturation * (luma - screen_color.r);
	//screen_color.g += screen_desaturation * (luma - screen_color.g);
	//screen_color.b += screen_desaturation * (luma - screen_color.b);

	//Desaturation according to average color
	//float avg_color = (screen_color.r + screen_color.g + screen_color.b) * 0.333;
	//screen_color = mix(screen_color,vec3(avg_color),screen_desaturation);


	//Crazy image flipping
	//vec2 new_uv = uv;
	//new_uv.x = (0.5 * (1.0/(-screen_desaturation + 0.5))) * (new_uv.x - 0.375) + 0.375;
	//vec3 screen_color = texture2D(tex_diff,new_uv).rgb;
	//if uv.x < 0, black
	//float black = (max(new_uv.x, 0.0) / new_uv.x);
	//screen_color *= black;
	//if uv.x > 0.75, black
	//black = (min(new_uv.x-0.75, 0.0) / (new_uv.x-0.75));
	//screen_color *= black;


	gl_FragColor = vec4(screen_color,1.0);
}