#version 430

#define POINT       0 
#define DIRECTIONAL 1
#define SPOT        2

#define ALBEDO_TEXTURE_MASK    (1 << 0);
#define SPECULAR_TEXTURE_MASK  (1 << 1);
#define NORMAL_TEXTURE_MASK    (1 << 2);
#define EMISSIVE_TEXTURE_MASK  (1 << 3);

in layout(location = 0) vec3 fposition;
in layout(location = 1) vec3 fnormal;
in layout(location = 2) vec2 ftexcoord;

out layout(location = 0) vec4 ocolor;

uniform struct Material
{
    uint params;
    vec3 albedo;
    vec3 specular;
    vec3 emissive;
    float shininess;

    vec2 tiling;
    vec2 offset;
} material;

uniform struct Light
{
   int type;
    vec3 position;
    vec3 direction;
    vec3 color;
    float range;
    float intesity;
    float innerangle;
    float outerangle;
} light[3];

uniform vec3 ambientLight;
uniform int numLights = 3;

layout(binding = 0) uniform sampler2D albedoTexture;
layout(binding = 1) uniform sampler2D specularTexture;
layout(binding = 2) uniform sampler2D normalTexture;
layout(binding = 3) uniform sampler2D emissiveTexture;

float attenuation(in vec3 position1, in vec3 position2, in float range)
{
	float distanceSqr = dot(position1 - position2, position1 - position2);
	float rangeSqr = pow(range, 2.0);
	float attenuation = max(0, 1 - pow((distanceSqr / rangeSqr), 2.0));
	attenuation = pow(attenuation, 2.0);
 
	return attenuation;
}

void phong(in Light light, in vec3 position, in vec3 normal, out vec3 diffuse, out vec3 specular)
{
 //diffuse
   vec3 lightDir = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(light.position - fposition);
   
   float spotIntensity = 1;
   if(light.type == SPOT)
   {
    float angle = acos(dot(light.direction, -lightDir));
    //if(angle > light.innerangle) spotIntensity = 0;
    spotIntensity = smoothstep(light.outerangle, light.innerangle, angle);

   }
   
    float intensity = max(dot(lightDir, normal), 0) * spotIntensity;
    diffuse = (light.color * intensity) * light.intesity;

    //specular 
    specular = vec3(0);
    if (intensity > 0)
    {
        vec3 reflection = reflect(-lightDir, fnormal);
        vec3 viewDir = normalize(-fposition);
        intensity = max(dot(reflection, viewDir), 0);
        intensity = pow(intensity, material.shininess);
        specular =  vec3(intensity * spotIntensity) ;
    } 
}

void main()
{	

    vec4 albedoColor = texture(albedoTexture, ftexcoord);//bool(material.params & ALBEDO_TEXTURE_MASK)?  : vec4(material.albedo, 1);
    vec4 specularColor = texture(specularTexture,ftexcoord);//vec4(material.specular,1);
    vec4 emissiveColor = texture(emissiveTexture,ftexcoord);//vec4(material.emissive,1);

    //set ambient and emissive colors
	ocolor = vec4(ambientLight, 1) * albedoColor + emissiveColor;
 
	// set lights
	for (int i = 0; i < numLights; i++)
	{
		vec3 diffuse;
		vec3 specular;
 
		float attenuation = (light[i].type == DIRECTIONAL) ? 1 : attenuation(light[i].position, fposition, light[i].range);
 
		phong(light[i], fposition, fnormal, diffuse, specular);
		ocolor += ((vec4(diffuse, 1) * albedoColor) + vec4(vec4(specular, 1)) * specularColor) * light[i].intesity * attenuation;
	}
}
