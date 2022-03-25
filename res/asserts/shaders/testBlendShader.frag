#version 330 core

out vec4 FragColor;

uniform vec3 color;
uniform mat4 model;

uniform sampler2D texture_ambient;
uniform sampler2D texture_diffuse;
in vec2 uv;

void main()
{
    // Ambient
    vec4 ambient = texture(texture_ambient, uv);

    // diffuse
    vec4 diffuse = texture(texture_diffuse, uv);

    // FragColor = vec4((ambient + diffuse).rgb, 1.0f);
    FragColor = ambient; //vec4(color, ambient.a); // + diffuse;
}