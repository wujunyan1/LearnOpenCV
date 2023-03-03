#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;


struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    sampler2D height;
    sampler2D ambient;
    float shininess;
}; 
uniform Material material;

struct Light {
    vec3 position;
    vec3 dir;

    vec3 diffuse;
    vec3 specular;
    vec3 ambient;
};
uniform Light light;

in vec2 uv;

void main()
{
    // Ambient
    vec4 ambient = texture(material.ambient, uv);

    // diffuse
    vec4 diffuse = texture(material.diffuse, uv);
    
    // height
    vec4 height = texture(material.height, uv);

    // normal
    vec4 normal = texture(material.normal, uv);

    //FragColor = vec4((ambient + diffuse).rgb, 1.0f);
    //FragColor = vec4(diffuse.r, 0, 0, 1.0f);
    FragColor = normal; // + diffuse;
}