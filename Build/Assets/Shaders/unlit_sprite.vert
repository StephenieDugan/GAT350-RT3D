#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;

out layout(location = 0) vec2 otexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform struct Material
{
    vec3 albedo;

    vec2 tiling;
    vec2 offset;
} material;

void main()
{
	otexCoord = (texCoord * material.tiling) + material.offset;

	//get world position
	vec3 vposition = model[3].xyz;
	//get size
	vec2 size = vec2(length(model[0]),length(model[1]));
	//get view right dir
	vec3 right = vec3(view[0][0],view[1][0],view[2][0]);
	//get view up dir
	vec3 up = vec3(view[0][1],view[1][1],view[2][1]);
	//set vertex position using world position adn view direction
	vposition = vposition + (position.x * right * size.x) + (position.y * up * size.y);

	mat4 vp = projection * view ;

	gl_Position = vp * vec4(vposition, 1.0);
}
