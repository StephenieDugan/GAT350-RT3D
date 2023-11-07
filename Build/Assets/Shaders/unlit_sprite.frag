#version 430

//in layout(location = 0) vec3 color;
in layout(location = 0) vec2 ftexCoord;

out layout(location = 0) vec4 ocolor;


layout (binding = 0) uniform sampler2D tex;

uniform struct Material
{
    vec3 albedo;

    vec2 tiling;
    vec2 offset;
} material;

void main()
{
	vec4 texColor = texture(tex, ftexCoord);

    if(texColor.a > 0.5) discard;
	ocolor = texColor * vec4(material.albedo,1);
}




//color * (sin(time)+1) * 0.5