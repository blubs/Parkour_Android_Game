precision mediump float;

//X component: black opacity
//Y component: white opacity
//Z component: subtle fade overlay opacity
uniform vec4 info;

void main()
{
	//Fade to black on the edges:
	vec2 uv = gl_FragCoord.xy;
	vec4 fade_color = vec4(0.0,0.0,0.0,0.0);
	fade_color.z = info.z * (pow(uv.x,4) + pow(uv.y,4));

	gl_FragColor = ((fade_color * (1.0 - info.x)) + (info.x * vec4(0.0,0.0,0.0,1.0)) * (1.0 - info.y)) + info.y * vec4(1.0,1.0,1.0,1.0);
}