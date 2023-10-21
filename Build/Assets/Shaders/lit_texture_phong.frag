#version 430

in layout(location = 1) vec2 ftexCoord;
in layout(location = 0) vec3 fposition;
in layout(location = 2) vec3 fnormal;

out layout(location = 0) vec4 ocolor;

layout (binding = 0) uniform sampler2D tex;

uniform struct Material
{
	vec3 diffuse;
	vec3 specular;
	float shininess;
 
	vec2 offset;
	vec2 tiling;
} material;

uniform struct Light
{
    vec3 position;
    vec3 color;
} light;

uniform vec3 ambientLight;

vec3 ads(in vec3 position, in vec3 normal)
{
    //Ambient
    vec3 ambient = ambientLight;


    //Diffuse
    vec3 lightDir = normalize(light.position - position);
    float intensity = max(dot(lightDir, normal), 0);
    vec3 diffuse = material.diffuse * (light.color * intensity);

    //specular
    vec3 specular = vec3(0);
    if( intensity>0) 
    { 
        vec3 reflection = reflect(-lightDir, normal);
        vec3 viewDir = -position;
        intensity = max(dot(reflection, viewDir),0);
        intensity = pow(intensity, material.shininess);
        specular = material.specular * intensity;

    }

    return ambient + diffuse + specular;
}


void main()
{
//applies tiling nad offset to texture coordinates
	vec4 texColor = texture(tex, (ftexCoord * material.tiling) + material.offset);
    //phong shading calculation
	ocolor = vec4(ads(fposition, normalize(fnormal)), 1);
}
