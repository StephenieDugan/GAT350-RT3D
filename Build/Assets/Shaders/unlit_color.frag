#version 430

in layout(location = 0) vec3 color;

out layout(location = 0) vec4 ocolor;

uniform float time;


void main()
{
	ocolor = vec4(color, 1);
}




//color * (sin(time)+1) * 0.5