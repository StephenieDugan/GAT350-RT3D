#version 430

in layout(location = 0) vec3 color;

out layout(location = 0) vec4 ocolor;

uniform float time;


void main()
{
	vec3 mcolor = vec3(color.r + color.g + color.b)/10 ;
	ocolor = vec4(1, 0,0, 1);
}




//color * (sin(time)+1) * 0.5