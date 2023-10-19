#version 430

in layout(location = 1) vec2 ftexCoord;
in layout(location = 0) vec3 fposition;
in layout(location = 2) vec3 fnormal;
in layout(location = 3) vec4 fcolor;

out layout(location = 0) vec4 ocolor;

layout (binding = 0) uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, ftexCoord);
	ocolor = texColor * fcolor;
}
