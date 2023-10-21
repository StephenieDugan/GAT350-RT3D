#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;

out layout(location = 1) vec2 otexcoord;
out layout(location = 0) vec3 oposition;
out layout(location = 2) vec3 onormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform struct Material
{
    vec3 diffuse;
    vec3 specular;
    float shininess;
    vec2 offset;
    vec2 tiling;
} material;

void main()
{
    mat4 modelView = view * model;

    //pass coordinates directly
    otexcoord = vtexcoord;
    //convert position and normal to world view space
    onormal = normalize(mat3(modelView) * vnormal);
    oposition = vec3(modelView * vec4(vposition, 1));
   
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(vposition, 1.0);
}
