#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;


struct Material {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
uniform Material[8] material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

in vec2 uv;

void main()
{
    // Ambient
    vec4 ambient = texture(material[0].ambient, uv);

    // diffuse
    vec4 diffuse = texture(material[0].diffuse, uv);

    //FragColor = vec4((ambient + diffuse).rgb, 1.0f);
    FragColor = diffuse; // + diffuse;
}