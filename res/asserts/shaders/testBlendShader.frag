#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

struct Material {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D shininess;
}; 
uniform Material material;

in vec2 uv;

void main()
{
    // Ambient
    vec4 ambient = texture(material.ambient, uv);

    // diffuse
    vec4 diffuse = texture(material.diffuse, uv);

    // FragColor = vec4((ambient + diffuse).rgb, 1.0f);
    FragColor = ambient; //vec4(color, ambient.a); // + diffuse;
}