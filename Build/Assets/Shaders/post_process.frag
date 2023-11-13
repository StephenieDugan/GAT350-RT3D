#version 430

 #define INVERT_MASK  (1<<0)
 #define GRAYSCALE_MASK  (1 << 1)
 #define COLORTINT_MASK  (1 << 2)

in layout(location = 0) vec2 ftexCoord;
out layout(location = 0) vec4 ocolor;

uniform float blend = 1;
uniform uint params = 0;

layout (binding = 0) uniform sampler2D screenTexture;

vec4 invert(vec4 color)
{
	return vec4(vec3(1) - color.rgb, color.a);
}

vec4 grayscale(in vec4 color)
{
	return vec4(vec3((color.r+color.b+color.g)/3), color.a);
}
vec4 colorTint(in vec4 color)
{
	return vec4(vec3((color.r+color.b+color.g)/3), color.a);
}

void main()
{
	vec4 baseColor = texture(screenTexture, ftexCoord);
	vec4 postprocess = baseColor;
	if (bool(params & INVERT_MASK)) postprocess = invert(postprocess);
	if (bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	if (bool(params & COLORTINT_MASK)) postprocess = colorTint(postprocess);

	ocolor = mix(baseColor, postprocess, blend);
}




//color * (sin(time)+1) * 0.5